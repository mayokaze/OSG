//
//  OSGDraggers.cpp
//  testlibx
//
//  Created by MayoKaze on 5/9/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#include "OSGDraggers.h"
#include "util"

OSGDraggers::OSGDraggers(t_stringlist names):m_names(names){}

OSGDraggers::~OSGDraggers(){}

DraggerSwitch* OSGDraggers::getScene(){
    pt_dragSwitch pDS = new DraggerSwitch();
    for(t_stringlist::iterator i =m_names.begin();i!=m_names.end() ;i++)
    {
        osgManipulator::Dragger* dragger = createDragger(*i);
        //dragger->setName(*i);
        dragger->setActivationKeyEvent('y');
        // dragger->setActivationKeyEvent('Y');
        pDS->addChild(dragger);
    }
    pDS->disable();
    return pDS.release();
}