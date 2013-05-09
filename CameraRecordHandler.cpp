//
//  CameraRecordHandler.cpp
//  testlibx
//
//  Created by MayoKaze on 5/8/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#include "CameraRecordHandler.h"
#include "DeSelectVisitor.h"
CameraRecordHandler::CameraRecordHandler():m_index(-1){}
CameraRecordHandler::~CameraRecordHandler(){}

bool CameraRecordHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa){
    if(osgViewer::Viewer *pViewer=dynamic_cast<osgViewer::Viewer*>(aa.asView())){
        if(ea.getEventType()==osgGA::GUIEventAdapter::KEYDOWN){
         switch(ea.getKey())
            {
                case osgGA::GUIEventAdapter::KEY_R:
                    recordCamera(pViewer);
                    return true;
                break;
                case osgGA::GUIEventAdapter::KEY_T:
                    switchCamera(pViewer);
                    return true;
                break;
            }
        }
    }
    return false;
}

void CameraRecordHandler::recordCamera(osgViewer::Viewer* v){
    osgGA::CameraManipulator *cm = NULL;
    std::cout<<matlist.size()<<std::endl;
  if ((cm = v->getCameraManipulator()) /*&&
      (matlist.empty()||cm->getInverseMatrix()!=matlist[matlist.size()-1])*/) {
        matlist.push_back(cm->getInverseMatrix());
    }
}

void CameraRecordHandler::switchCamera(osgViewer::Viewer* v){
    osgGA::CameraManipulator *cm = NULL;
	if (!(cm = v->getCameraManipulator())||matlist.empty()) {
		return;
	}
    m_index = getIndex();
    cm->setByInverseMatrix(matlist[m_index]);
    std::cout<<m_index<<" - " <<matlist.size()<<std::endl;
    DeSelectVisitor dv;
    v->getSceneData()->accept(dv);
    dv.deSelectNode();
}