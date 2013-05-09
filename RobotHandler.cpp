//
//  RobotHandler.cpp
//  testlibx
//
//  Created by MayoKaze on 4/29/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//
#include <osgGA/GUIEventHandler>
#include <osg/Node>
#include <osgViewer/Viewer>
#include "RobotHandler.h"
#include "RobotUpdator.h"
#include "findNodeVisitor.h"
#include "type.h"

RobotHandler::RobotHandler(){}
RobotHandler::~RobotHandler(void){}

void RobotHandler::operator()(osg::Node *node, osg::NodeVisitor *nv)
{
    pt_robotUpdator ru = dynamic_cast<class RobotUpdator *>(node->getUserData() );
    if(ru)
    {
        if (nv->getVisitorType()==osg::NodeVisitor::EVENT_VISITOR)
        {
            osgGA::EventVisitor *ev = dynamic_cast<osgGA::EventVisitor *>(nv);
            if (ev)
            {
                //osgGA::GUIActionAdapter* aa = ev->getActionAdapter();
                osgGA::EventQueue::Events& events = ev->getEvents();
                for(osgGA::EventQueue::Events::iterator itr=events.begin();
                    itr!=events.end(); ++itr)
                {
                    handle(*(*itr),node);
                }
            }
        }
    }
    traverse(node, nv);
}

bool RobotHandler::handle( const osgGA::GUIEventAdapter &ea,osg::Node *robot)
{
	if(robot)
	{
        RobotUpdator *ru = dynamic_cast<RobotUpdator *>(robot->getUserData());
        if (ea.getEventType()==osgGA::GUIEventAdapter::KEYDOWN) {
            std::string keys = "bBlLuUhHjJkK";
            if (keys.npos !=   keys.find_first_of(ea.getKey())) {
                ru->pressKey(ea.getKey());
            }
         

        }
        else if(ea.getEventType()==osgGA::GUIEventAdapter::KEYUP){
            std::string keys = "bBlLuUhHjJkK";
            if (keys.npos != keys.find_first_of(ea.getKey())) {
                ru->releaseKey(ea.getKey());
            }
            return true;
        }
	}
	return false;
}