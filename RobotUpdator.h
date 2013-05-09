//
//  RobotData.h
//  testlibx
//
//  Created by MayoKaze on 4/28/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__RobotData__
#define __testlibx__RobotData__

#include <osg/Node>
#include <osgSim/DOFTransform>
#include <osg/NodeVisitor>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Drawable>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <map>
#include "Commander.h"
#include "util"
class RobotUpdator : public osg::Referenced
{
public:
    RobotUpdator(osg::Node*,double* as=NULL);
    virtual ~RobotUpdator();
 //   void applyRotation();
    void pressKey(char key);
    void releaseKey(char key);
    void updateRotation();
    inline bool onRotation(){
        return NULL != onRotCmd;
    };

protected:
    osg::Node* robot;

    Commander *onRotCmd;
    std::map<char,Commander*> commandMap;
   // std::map<const char*,osg::Vec4f> rotMap;
    osg::Switch* findSwitch(osg::Group* node);
   // void setGeodeColor( osg::Geode* node, const osg::Vec4& color );
   // void setNodeColor( osg::Node* node, const osg::Vec4& newColor );
   // void resetNodeColor(osg::Node* node);
};



#endif /* defined(__testlibx__RobotData__) */
