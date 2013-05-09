//
//  DraggerSwitchHandler.cpp
//  testlibx
//
//  Created by MayoKaze on 5/9/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#include <osgViewer/Viewer>
#include "FindNodeVisitor.h"
#include "DraggerSwitchHandler.h"
#include "type.h"

DraggerSwitchHandler::DraggerSwitchHandler(){}

DraggerSwitchHandler::~DraggerSwitchHandler(){}

bool DraggerSwitchHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa){
    if(osgViewer::Viewer *pViewer=dynamic_cast<osgViewer::Viewer*>(aa.asView())){
        if(ea.getEventType()==osgGA::GUIEventAdapter::KEYDOWN&&ea.getKey()==osgGA::GUIEventAdapter::KEY_Down){
            FindNodeVisitor fv("draggers");
            pViewer->getSceneData()->accept(fv);
            pt_dragSwitch pDS = dynamic_cast <DraggerSwitch *>(fv.getFirst());
            float scale;
            pDS->currentDragger();
            if( pDS->currentDragger()){
             pDS->currentDragger()->getUserValue("scale", scale);
             pt_matrixTrans pTM = dynamic_cast <osg::MatrixTransform *> (pDS->currentDragger()->getUserData());
             pDS->nextDragger(pTM, scale);
             return true;
            }
         }
    }
    return false;

}