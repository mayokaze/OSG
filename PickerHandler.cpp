//
//  PickerHandler.cpp
//  testlibx
//
//  Created by MayoKaze on 5/8/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#include "PickerHandler.h"
#include <osgFX/Scribe>
#include <osg/MatrixTransform>
#include <osg/vec3>
#include <osgGA/TrackballManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgManipulator/Dragger>
#include "type.h"
#include "util"
#include "DeSelectVisitor.h"
#include "FindNodeVisitor.h"


PickHandler::PickHandler(){};
PickHandler:: ~PickHandler(){};

bool  PickHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa){
    if(osgViewer::Viewer *pViewer=dynamic_cast<osgViewer::Viewer*>(aa.asView())){
        if(ea.getEventType() == osgGA::GUIEventAdapter::PUSH){
            pt_lsi picker =new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW, ea.getX(), ea.getY());
            osgUtil::IntersectionVisitor iv(picker);
            pViewer->getCamera()->accept(iv);
            pt_node node = 0;
            pt_group parent = 0;
            if (picker->containsIntersections())
            {
                osgUtil::LineSegmentIntersector::Intersection intersection = picker->getFirstIntersection();
                osg::NodePath& nodePath = intersection.nodePath;
                node = (nodePath.size()>=1)?nodePath[nodePath.size()-1]:0;
                parent = (nodePath.size()>=2)?dynamic_cast<osg::Group*>(nodePath[nodePath.size()-2]):0;
                
                for(int i=0;i<nodePath.size();i++){
                    if (dynamic_cast<osgManipulator::Dragger*>(nodePath[i])) {
                        return false;
                    }
                }
                
                if (ea.getButton()==osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON){
                    //manipulate(ea.getX(), ea.getY(),pViewer);
                    pick(parent, node,pViewer);
                }
                else if(ea.getButton()==osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON){
                   // modify(ea.getX(), ea.getY(),pViewer);
                    if( node->getName().length()==0){
                        pick(NULL,NULL,pViewer);
                        focus(parent,node,pViewer);
                        modify(parent, node,pViewer);
                    }
                }
                
            }
            else if(ea.getButton()==osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
                  pick(NULL,NULL,pViewer);
         return true;
        }
   }
    return false;

}
                                        
/*void PickHandler::manipulate(float x, float y,osgViewer::Viewer* viewer){
    pt_lsi picker =new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW, x, y);
    osgUtil::IntersectionVisitor iv(picker);
    viewer->getCamera()->accept(iv);
    pt_node node = 0;
    pt_group parent = 0;
    if (picker->containsIntersections())
    {
        osgUtil::LineSegmentIntersector::Intersection intersection = picker->getFirstIntersection();
        osg::NodePath& nodePath = intersection.nodePath;
        node = (nodePath.size()>=1)?nodePath[nodePath.size()-1]:0;
        parent = (nodePath.size()>=2)?dynamic_cast<osg::Group*>(nodePath[nodePath.size()-2]):0;
        pick(parent, node,viewer);
    }
}*/

void PickHandler::modify(osg::Group* parent,osg::Node* node,osgViewer::Viewer* v){
    FindNodeVisitor fv("draggers");
    v->getSceneData()->accept(fv);
    osg::MatrixTransform *pMT = dynamic_cast <osg::MatrixTransform *>(parent);
    if(!pMT) return;
    float scale;
    node->getUserValue("scale",scale);
    pt_dragSwitch pDS = dynamic_cast <DraggerSwitch *> (fv.getFirst());
    if(!pDS) return;
    pDS->disable();
    pDS->nextDragger(pMT,scale);
}


void PickHandler::focus(osg::Group* parent,osg::Node* node,osgViewer::Viewer* v){
   // std::cout<< "test"<<std::endl;
    if(pt_matrixTrans pMT = dynamic_cast<osg::MatrixTransform*>(parent)){
        osg::Vec3  trans =  pMT->getMatrix().getTrans();
        osgGA::CameraManipulator *cm = v->getCameraManipulator();
        osgGA::KeySwitchMatrixManipulator *km =  dynamic_cast<osgGA::KeySwitchMatrixManipulator*>(cm);
        if(km){
            if(osgGA::TrackballManipulator *tm = dynamic_cast<osgGA::TrackballManipulator*>(km->getMatrixManipulatorWithIndex(0))){
                tm->setCenter(trans);
                km->selectMatrixManipulator(0);
            }
            
        }
        
    }
    else if(node->getName().length()>0&&node->getName() != "prim"){
        //&&std::string::npos == node->getName().find("Dragger")
       // std::cout<< node->getName()<<std::endl;
        FindNodeVisitor fv("robot");
        v->getSceneData()->accept(fv);
        osg::MatrixTransform *pMT = dynamic_cast <osg::MatrixTransform *> (fv.getFirst());
        if(pMT){
            osg::Vec3  trans =  pMT->getMatrix().getTrans();
            osgGA::CameraManipulator *cm = v->getCameraManipulator();
            osgGA::KeySwitchMatrixManipulator *km =  dynamic_cast<osgGA::KeySwitchMatrixManipulator*>(cm);
            if(osgGA::TrackballManipulator *tm = dynamic_cast<osgGA::TrackballManipulator*>(km->getMatrixManipulatorWithIndex(0))){
                tm->setCenter(trans);
                km->selectMatrixManipulator(0);
            }
        }
    }
}

void PickHandler::pick(osg::Group* parent,osg::Node* node,osgViewer::Viewer* v)
{

    DeSelectVisitor dv;
    v->getSceneData()->accept(dv);
    dv.deSelectNode();
    FindNodeVisitor fv("draggers");
    v->getSceneData()->accept(fv);
    pt_dragSwitch pDS = dynamic_cast <DraggerSwitch *> (fv.getFirst());
    if (pDS) {
        pDS->disable();
    }

    if (!parent || !node) return;
    
 //   std::cout<<"  parent "<<parent->className()<<std::endl;

    pt_scribe parentAsScribe = dynamic_cast<osgFX::Scribe*>(parent);
    if (!parentAsScribe)
    {
        // node not already picked, so highlight it with an osgFX::Scribe
        //remove previous selection
        osgFX::Scribe* scribe = new osgFX::Scribe();
        scribe->setWireframeColor(csg_greenv);
        scribe->addChild(node);
        parent->replaceChild(node,scribe);
          //  osg::MatrixTransform *mt = dynamic_cast <osg::MatrixTransform *> (finder.getFirst());
        focus(parent, node, v);

    }
}