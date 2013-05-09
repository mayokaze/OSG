//
//  OSGShape.h
//  testlibx
//
//  Created by MayoKaze on 5/6/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__OSGShape__
#define __testlibx__OSGShape__
#include "util"
#include "OSGDrawable.h"
#include <iostream>
#include <osg/MatrixTransform>
#include <osg/Node>




class OSGShape:public OSGDrawable
{
public:
    enum Kind {sphere,cone,capsule,texture} kind;
	OSGShape(osg::Matrix,float*,Kind);
	virtual ~OSGShape(void);
    virtual osg::MatrixTransform* getScene(float scale = 4.0f);

private:
    osg::Node*  makeShape(float scale);

    
};
#endif