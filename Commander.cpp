//
//  Commander.cpp
//  testlibx
//
//  Created by MayoKaze on 4/29/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#include "Commander.h"
Commander:: Commander(){}
Commander::~Commander(void){}
Commander::Commander(std::string name,osg::Vec3f ax,float spd,short min,short max,char k,bool b){
    nodeName = name;
    axis = ax;
    speed = spd;
    minDegree = min;
    maxDegree = max;
    blocked = b;
    key = k;
}