//
//  FileHandler.h
//  testlibx
//
//  Created by MayoKaze on 5/9/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__FileHandler__
#define __testlibx__FileHandler__


#include <iostream>
#include <osgGA/GUIEventHandler>
class FileHandler : public osgGA::GUIEventHandler{
public:
	FileHandler();
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
    virtual  ~FileHandler();
    
private:
    //void
};
#endif /* defined(__testlibx__FileHandler__) */
