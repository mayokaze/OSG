//
//  FxHandler.cpp
//  testlibx
//
//  Created by MayoKaze on 5/8/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#include "FxHandler.h"
#include "FindNodeVisitor.h"
#include "type.h"
FXHandler::FXHandler():m_fxOn(false){}
FXHandler::~FXHandler(){}

bool FXHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa){
    if(osgViewer::Viewer *pViewer=dynamic_cast<osgViewer::Viewer*>(aa.asView())){
        if(ea.getEventType()==osgGA::GUIEventAdapter::KEYDOWN&&ea.getKey()==osgGA::GUIEventAdapter::KEY_D){
            toggleFX(pViewer);
            return true;
        }
      }
     return false;
}

void FXHandler::toggleFX(osgViewer::Viewer* v){
    FindNodeVisitor fv("fx");
    v->getSceneData()->accept(fv);
    pt_switch pSwitch = dynamic_cast<osg::Switch*>(fv.getFirst());
    if (pSwitch) {
          m_fxOn = !m_fxOn;
        m_fxOn ? pSwitch->setAllChildrenOn():pSwitch->setAllChildrenOff();
    }
  
}
