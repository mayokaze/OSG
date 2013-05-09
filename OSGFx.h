//
//  OSGFx.h
//  testlibx
//
//  Created by MayoKaze on 5/8/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__OSGFx__
#define __testlibx__OSGFx__

#include <iostream>
#include "util"
#include "OSGDrawable.h"
#include <osg/Switch>
class OSGFx
{
public:
    OSGFx();
	virtual ~OSGFx(void);
    osg::Switch* getScene();
    
private:
   // osg::Node*  makeShape(float fDim);
};
#endif /* defined(__testlibx__OSGFx__) */
