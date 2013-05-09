//
//  DraggerSwitch.cpp
//  testlibx
//
//  Created by MayoKaze on 5/9/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#include "DraggerSwitch.h"
#include <osgManipulator/Dragger>
#include <osg/ValueObject>

DraggerSwitch::DraggerSwitch(void):m_index(-1){}

DraggerSwitch::~DraggerSwitch(){};

int DraggerSwitch::nextDragger(osg::MatrixTransform* mt,float scale){
    removeTrans();
    if(m_index >= getNumChildren()-1)
        m_index = -1;
    setSingleChildOn(++m_index);
    currentDragger()->setMatrix(osg::Matrix::scale(scale*2.5, scale*2.5, scale*2.5) *
                                     osg::Matrix::translate(mt->getMatrix().getTrans()));
    currentDragger()->addTransformUpdating(mt);
    currentDragger()->setHandleEvents(true);
    currentDragger()->setUserData(mt);
    currentDragger()->setUserValue("scale",scale);
    std::cout<<m_index<<std::endl;
    return m_index;
}

void DraggerSwitch::disable(){
    setAllChildrenOff();
    removeTrans();
    m_index = -1;
}

void DraggerSwitch::removeTrans(){
    if (m_index == -1) return;
    osgManipulator::Dragger* drg = dynamic_cast<osgManipulator::Dragger*>(getChild(m_index));
    if(osg::MatrixTransform *pMT = dynamic_cast<osg::MatrixTransform*>(drg->getUserData())){
        drg->removeTransformUpdating(pMT);
        drg->setUserValue("scale", 0);
        drg->setUserData(NULL);
    }

}