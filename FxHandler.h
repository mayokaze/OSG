//
//  FxHandler.h
//  testlibx
//
//  Created by MayoKaze on 5/8/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__FxHandler__
#define __testlibx__FxHandler__

#include <iostream>
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osg/Matrix>


class FXHandler : public osgGA::GUIEventHandler{
public:
	FXHandler();
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
    virtual  ~FXHandler();
    
private:
    void toggleFX(osgViewer::Viewer*);
    bool m_fxOn;
};
#endif /* defined(__testlibx__FxHandler__) */
