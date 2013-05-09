//
//  RobotCallback.cpp
//  testlibx
//
//  Created by MayoKaze on 5/5/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#include "RobotCallback.h"
#include "RobotUpdator.h"
#include "type.h"

void RobotCallback::operator()(osg::Node *node, osg::NodeVisitor *nv)
{
    pt_robotUpdator ru = dynamic_cast<class RobotUpdator *> (node->getUserData());
    if(ru&&ru->onRotation())
    {
        ru->updateRotation();
    }
    traverse(node, nv);
}