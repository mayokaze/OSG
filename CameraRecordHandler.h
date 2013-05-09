//
//  CameraRecordHandler.h
//  testlibx
//
//  Created by MayoKaze on 5/8/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__CameraRecordHandler__
#define __testlibx__CameraRecordHandler__
#include <iostream>
#include <osgGA/GUIEventHandler>
#include <osgViewer/Viewer>
#include <osg/Matrix>

#include <vector>
class CameraRecordHandler : public osgGA::GUIEventHandler{
public:
	CameraRecordHandler();
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
    virtual  ~CameraRecordHandler();
    
private:
    std::vector<osg::Matrix> matlist;
    int m_index;
    void recordCamera(osgViewer::Viewer*);
    void switchCamera(osgViewer::Viewer*);
    inline int getIndex(){return m_index >= matlist.size()-1 ? m_index=0 : ++m_index;};
};
#endif /* defined(__testlibx__CameraRecordHandler__) */
