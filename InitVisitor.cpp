//
//  InitVisitor.cpp
//  testlibx
//
//  Created by MayoKaze on 4/30/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//
#include <osg/StateSet>
#include <osg/Material>
#include <osg/StateAttribute>
#include <osg/Node>
#include <osgSim/DOFTransform>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Geometry>
#include <osg/Drawable>
#include <osg/ShapeDrawable>
#include <osg/Switch>

#include "InitVisitor.h"
#include "type.h"
#include "OSGFx.h"
#include "OSGDraggers.h"
InitVisitor::InitVisitor(void) : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
{
}


InitVisitor::~InitVisitor(void)
{
}

void InitVisitor::apply(osg::Node &searchNode)
{
    if (std::string::npos != searchNode.getName().find("_Rotator"))
    {
        
      
        pt_group pOrig = new osg::Group;
        
        pt_group pRed = new osg::Group;
        pt_group pGeen = new osg::Group;
        unsigned int numGeoms = searchNode.asGroup()->getNumChildren();
        for( unsigned int geodeIdx = 0; geodeIdx < numGeoms; geodeIdx++ )
        {
            //   std::cout<<"set" << numGeoms << std::endl;
            osg::Geode *pGeode =  dynamic_cast <osg::Geode *> (searchNode.asGroup()->getChild(geodeIdx));
       
            if(pGeode){
           //     std::cout << ge->className() << " Name: " << ge->getName()<<"==="<<std::endl;
            pOrig->addChild(pGeode);
            pRed->addChild(pGeode);
            pGeen->addChild(pGeode);
            }
    
        }
        

        pt_switch pSwitch = new osg::Switch;
        pSwitch->addChild(pOrig, true);
        pSwitch->addChild(pRed,false);
        pSwitch->addChild(pGeen,false);
        setGroupColor (pGeen, csg_greenv);
        setGroupColor (pRed,csg_redv);

    
        unsigned int num = pOrig->getNumChildren();
        for( unsigned int i = 0; i < num; i++ )
        {
            osg::Geode *pGeode =  dynamic_cast <osg::Geode *> (pOrig->getChild(i));
            if(pGeode){
           //   std::cout << ge->className() << " Name: " << ge->getName()<<"+++"<<std::endl;
                searchNode.asGroup()->removeChild(pGeode);}
        }
        
        
        searchNode.asGroup()->addChild(pSwitch);
      }
    else if(searchNode.getName() == "manip"){
        OSGFx fx = OSGFx();
        pt_switch s = fx.getScene();
        searchNode.asGroup()->addChild(s);
        t_stringlist dnames;
        dnames.push_back("TrackballDragger");
        dnames.push_back("TabBoxDragger");
        dnames.push_back("TranslateAxisDragger");
        dnames.push_back("Translate2DDragger");
       // dnames.push_back("TabPlaneDragger");
        OSGDraggers ods(dnames);
        DraggerSwitch* pDS =  ods.getScene();
        pDS->setName("draggers");
        searchNode.asGroup()->addChild(pDS);
    }
    traverse(searchNode);
}


/*
 osg::Node* addDraggerToScene(osg::Node* scene, const std::string& name, float scale_factor)
 {
 scene->getOrCreateStateSet()->setMode(GL_NORMALIZE, osg::StateAttribute::ON);
 
 osg::MatrixTransform* selection = new osg::MatrixTransform;
 selection->addChild(scene);
 
 osgManipulator::Dragger* dragger = createDragger(name);
 
 osg::Group* root = new osg::Group;
 root->addChild(selection);
 
 root->addChild(dragger);
 
 float scale = scene->getBound().radius() * scale_factor;
 dragger->setMatrix(osg::Matrix::scale(scale, scale, scale) *
 osg::Matrix::translate(scene->getBound().center()));//dragger自身MAT
 
 dragger->addTransformUpdating(selection);//随selction运动
 
 // we want the dragger to handle it's own events automatically
 dragger->setHandleEvents(true);
 
 // if we don't set an activation key or mod mask then any mouse click on
 // the dragger will activate it, however if do define either of ActivationModKeyMask or
 // and ActivationKeyEvent then you'll have to press either than mod key or the specified key to
 // be able to activate the dragger when you mouse click on it.  Please note the follow allows
 // activation if either the ctrl key or the 'a' key is pressed and held down.
 dragger->setActivationModKeyMask(osgGA::GUIEventAdapter::MODKEY_ALT)  ;
 dragger->setActivationKeyEvent('a');
 
 return root;
 }*/

/*
// dragger node test
osg::Group *dg = new osg::Group;
dg->addChild(genDraggerNode("TabBoxDragger", 1.5f));

osg::MatrixTransform *dt = new osg::MatrixTransform;
osg::Matrixd mt; mt.setTrans(3.5, 0, 0);
dt->setMatrix(mt);
dt->addChild(genDraggerNode("TrackballDragger", 0.85f));

dg->addChild(dt);
pSwitchNode->addChild(dg);*/

void InitVisitor::setGroupColor( osg::Group* node, const osg::Vec4& color )
{
    //  std::cout << node->className() << std::endl;
    if( node == 0 ) return;
    
    osg::Material *pMat = dynamic_cast<osg::Material*>( node->getOrCreateStateSet()->getAttribute( osg::StateAttribute::MATERIAL ) );
    if ( !pMat )
    {
        
        pMat = new osg::Material();
        
        node->getOrCreateStateSet()->setAttribute(pMat, osg::StateAttribute::MATERIAL);
        
    }
    // mat->setDiffuse( osg::Material::FRONT_AND_BACK, color );
    //mat->setColorMode(osg::Material::ColorMode::SPECULAR);
    pMat->setSpecular(osg::Material::FRONT_AND_BACK, color);
    
}

/*
void InitVisitor::setGeodeColor( osg::Geode* node, const osg::Vec4& color )
{
    //  std::cout << node->className() << std::endl;
    if( node == 0 ) return;
    
    osg::Material* mat =
    dynamic_cast<osg::Material*>( node->getOrCreateStateSet()->getAttribute( osg::StateAttribute::MATERIAL ) );
    if ( !mat )
    {
        
        mat = new osg::Material();
        
        node->getOrCreateStateSet()->setAttribute(mat, osg::StateAttribute::MATERIAL);
        
    }
    // mat->setDiffuse( osg::Material::FRONT_AND_BACK, color );
    mat->setColorMode(osg::Material::ColorMode::SPECULAR);
    mat->setSpecular(osg::Material::FRONT_AND_BACK, color);
}*/

/*void InitVisitor::setNodeColor( osg::Node* node, const osg::Vec4& newColor )
{
    
    unsigned int numGeoms = node->asGroup()->getNumChildren();
    for( unsigned int geodeIdx = 0; geodeIdx < numGeoms; geodeIdx++ )
    {
        //   std::cout<<"set" << numGeoms << std::endl;
        osg::Geode* ge =  dynamic_cast <osg::Geode*> (node->asGroup()->getChild(geodeIdx));
        if(ge)
            setGeodeColor(ge, newColor );
    }
}*/