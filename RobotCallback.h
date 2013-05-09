//
//  RobotCallback.h
//  testlibx
//
//  Created by MayoKaze on 5/5/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__RobotCallback__
#define __testlibx__RobotCallback__

#include <iostream>
#include <osg/Node>
#include <osg/NodeVisitor>

class RobotCallback : public osg::NodeCallback
{
public:
    virtual void operator()(osg::Node *node, osg::NodeVisitor *nv);
};

#endif /* defined(__testlibx__RobotCallback__) */
