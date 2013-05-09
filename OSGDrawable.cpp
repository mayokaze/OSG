//
//  OSGDrawable.cpp
//  testlibx
//
//  Created by MayoKaze on 5/8/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#include "OSGDrawable.h"



OSGDrawable::OSGDrawable(osg::Matrix t,float* c){
    isGenColor = false;
    if(!c)
        initC();
    else
        color = c;
    trans = t;
}

OSGDrawable::~OSGDrawable(){
    if (isGenColor) {
        delete color;
    }
}

void OSGDrawable::initC(){
    // std::cout<<"testcl"<<std::endl;
    color = new float[4];
    isGenColor = true;
    randColor(color);

}

osg::MatrixTransform* OSGDrawable::getScene(float scale){return NULL;}