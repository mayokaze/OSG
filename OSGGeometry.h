//
//  OSGVertex.h
//  testlibx
//
//  Created by MayoKaze on 5/8/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__OSGVertex__
#define __testlibx__OSGVertex__

#include <iostream>
#include "util"
#include <iostream>
#include <osg/Vec4>
#include <osg/Matrixf>
#include <osg/MatrixTransform>
#include <osg/Node>
#include "OSGDrawable.h"



class OSGGeometry :public OSGDrawable
{
public:
    enum Kind {light,pure/*,texture*/} kind;
    OSGGeometry(osg::Matrix,float*,Kind);
	virtual ~OSGGeometry(void);
    virtual osg::MatrixTransform* getScene(float scale = 4.0f);
    
private:
    osg::Node*  makeGeo(float);
};


#endif /* defined(__testlibx__OSGVertex__) */
