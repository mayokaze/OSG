//
//  SaveVisitor.cpp
//  testlibx
//
//  Created by MayoKaze on 5/9/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#include "SaveVisitor.h"
#include <osg/MatrixTransform>
#include "type.h"
SaveVisitor::SaveVisitor(PrettyWriter<FileStream>* w):osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ACTIVE_CHILDREN),writer(w){}

SaveVisitor::~SaveVisitor(){}

void SaveVisitor::apply(osg::Node& node){
    std::string ts ;
    if (node.getName() == "draggers") {
        return;
    }
    else if (node.getName()=="prim"){
        pt_matrixTrans mtx = dynamic_cast<osg::MatrixTransform*>(&node);
        pt_node child = node.asGroup()->getChild(0);
       // child->getOrCreateStateSet()->get
        
        osg::Material *pMat = dynamic_cast<osg::Material*>( child->getOrCreateStateSet()->getAttribute( osg::StateAttribute::MATERIAL ) );
        osg::Vec4 color = pMat->getSpecular(osg::Material::FRONT);

        osg::Matrix mat = mtx->getMatrix();
        
        float scale;
        
        osg::Vec3d trans;
        osg::Vec3d scalev;
        osg::Quat quat;
        trans  = mat.getTrans();
        scalev = mat.getScale();
        quat = mat.getRotate();
        
        
        writer->StartObject();
        writer->String("type");
        child->getUserValue("kind", ts);
        writer->String(ts.c_str());
        writer->String("quat");
        writer->StartArray();
        
        writer->Double(quat[0]);
        writer->Double(quat[1]);
        writer->Double(quat[2]);
        writer->Double(quat[3]);
        writer->EndArray();
        writer->String("scalev");
        writer->StartArray();
        
        writer->Double(scalev[0]);
        writer->Double(scalev[1]);
        writer->Double(scalev[2]);
      //  writer->Double(scalev[3]);
        writer->EndArray();
        writer->String("trans");
        writer->StartArray();
        
        writer->Double(trans[0]);
        writer->Double(trans[1]);
        writer->Double(trans[2]);
    //    writer->Double(trans[3]);
        writer->EndArray();
        writer->String("color");
        writer->StartArray();
        
        writer->Double(color[0]);
        writer->Double(color[1]);
        writer->Double(color[2]);
        writer->Double(color[3]);
        writer->EndArray();
        writer->String("scale");
        child->getUserValue("scale",scale);
        std::cout<<scale<<std::endl;

        writer->Double(scale);
        writer->EndObject();
        return;
    }
    else if (node.getName()=="robot"){
    //    pt_matrixTrans mtx = dynamic_cast<osg::MatrixTransform*>(&node);
        node.getUserValue("path", ts);
        writer->StartObject();
        writer->String("type");
        writer->String("model");
        writer->String("path");
        writer->String(ts.c_str());
        writer->EndObject();
     }
    else if (std::string::npos != node.getName().find("_Rotator")){
        pt_matrixTrans mtx = dynamic_cast<osg::MatrixTransform*>(&node);
        osg::Quat quat;
        mtx->getMatrix().get(quat);
        writer->StartObject();
        writer->String("type");
        writer->String(node.getName().c_str());
        writer->String("quat");
        writer->StartArray();
        writer->Double(quat[0]);
        writer->Double(quat[1]);
        writer->Double(quat[2]);
        writer->Double(quat[3]);
        writer->EndArray();
        writer->EndObject();
        /*if (node.getName()=="Hand3_Rotator") {
            writer->EndObject();
        }*/
     
        
    }
     traverse(node);
}