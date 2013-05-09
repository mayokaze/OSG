//
//  RobotHandler.h
//  testlibx
//
//  Created by MayoKaze on 4/29/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__RobotHandler__
#define __testlibx__RobotHandler__



#include <osg/PolygonMode>
#include <osgGA/GUIEventHandler>


class RobotHandler: public osg::NodeCallback
{
public:
	RobotHandler();
	virtual ~RobotHandler(void);
    virtual void operator()(osg::Node *node, osg::NodeVisitor *nv);
	virtual bool handle(const osgGA::GUIEventAdapter &ea,osg::Node *robot);
};



#endif /* defined(__testlibx__RobotHandler__) */
