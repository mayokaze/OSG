//
//  InitHelper.cpp
//  testlibx
//
//  Created by MayoKaze on 5/9/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#include "InitHelper.h"
#include "type.h"
#include "RobotHandler.h"
#include "RobotCallback.h"
#include "RobotUpdator.h"
#include <osgdb/ReadFile>
osg::Group* initScene(std::string  path){
	pt_group root= new osg::Group();
    pt_group manip = new osg::Group();
    root->addChild(manip);
    pt_node model = osgDB::readNodeFile (path);
    model->setUserValue("path", path);
    model->setName("robot");
    manip->addChild(model);
    manip->setName("manip");
   // RobotUpdator* ru = new RobotUpdator(model);
    pt_robotUpdator ru = new RobotUpdator(model);
    model ->setUserData(ru);
    model ->setUpdateCallback(new RobotCallback);
    model->addEventCallback(new RobotHandler);
    return root.release();
}