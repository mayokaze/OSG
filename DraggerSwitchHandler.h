//
//  DraggerSwitchHandler.h
//  testlibx
//
//  Created by MayoKaze on 5/9/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__DraggerSwitchHandler__
#define __testlibx__DraggerSwitchHandler__

#include <iostream>
#include <osgGA/GUIEventHandler>
class DraggerSwitchHandler : public osgGA::GUIEventHandler{
public:
	DraggerSwitchHandler();
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
    virtual  ~DraggerSwitchHandler();
    
private:
 
};
#endif /* defined(__testlibx__DraggerSwitchHandler__) */
