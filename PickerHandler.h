//
//  PickerHandler.h
//  testlibx
//
//  Created by MayoKaze on 5/8/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__PickerHandler__
#define __testlibx__PickerHandler__

#include <iostream>
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osg/Group>




class PickHandler : public osgGA::GUIEventHandler{
public:
	PickHandler();
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
    virtual  ~PickHandler();
    
protected:
	//void Pick();
	void pick(osg::Group* parent, osg::Node* node,osgViewer::Viewer*);
    void focus (osg::Group* parent, osg::Node* node,osgViewer::Viewer*);
   // void manipulate(float x, float y,osgViewer::Viewer*);
    void modify(osg::Group* parent, osg::Node* node,osgViewer::Viewer*);
};
#endif /* defined(__testlibx__PickerHandler__) */
