//
//  AddEventHandler.h
//  testlibx
//
//  Created by MayoKaze on 5/8/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__AddEventHandler__
#define __testlibx__AddEventHandler__

#include <osgGA/GUIEventHandler>
#include <iostream>
class AddEventHandler: public osgGA::GUIEventHandler
{
public:
	AddEventHandler();
	virtual ~AddEventHandler(void);
    
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa, osg::Object *, osg::NodeVisitor*);
    
protected:
    
    
};
#endif /* defined(__testlibx__AddEventHandler__) */
