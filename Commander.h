//
//  Commander.h
//  testlibx
//
//  Created by MayoKaze on 4/29/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__Commander__
#define __testlibx__Commander__

#include <iostream>
#include <string>
#include <osg/Vec3f>
class Commander{
public:
    Commander();
	Commander(std::string,osg::Vec3f,float,short,short,char,bool b =false);
	virtual ~Commander(void);
    std::string nodeName;
    osg::Vec3f axis;
    float speed;
    short minDegree;
    short maxDegree;
    bool blocked;
    char key;
};
#endif /* defined(__testlibx__Commander__) */
