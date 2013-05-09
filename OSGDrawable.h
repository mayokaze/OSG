//
//  OSGDrawable.h
//  testlibx
//
//  Created by MayoKaze on 5/8/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__OSGDrawable__
#define __testlibx__OSGDrawable__

#include "util"
#include <iostream>
#include <osg/Vec4>
#include <osg/Matrixf>
#include <osg/MatrixTransform>
#include <osg/Node>
class OSGDrawable
{
public:
    //enum Kind {sphere,box,capsule} kind;
	OSGDrawable(osg::Matrix,float*);
	virtual ~OSGDrawable(void);
    virtual osg::MatrixTransform* getScene(float scale = 4.0f);
    
protected:
    osg::Matrixf trans;
    float *color;
    bool isGenColor;
    void initC();
    
    
    
};
#endif /* defined(__testlibx__OSGDrawable__) */
