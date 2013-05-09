//
//  RobotData.cpp
//  testlibx
//
//  Created by MayoKaze on 4/28/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#include "RobotUpdator.h"
#include "FindNodeVisitor.h"
#include <iostream>
#include <osg/StateSet>
#include <osg/Material>
#include <osg/StateAttribute>
#include <osg/Quat>
#include <ctype.h>
#include <osg/Switch>
#include "type.h"


RobotUpdator::RobotUpdator(osg::Node *n,double *as)
:robot(n),onRotCmd(NULL)
{
  
  commandMap['k'] = new Commander("Hand3_Rotator",osg::Vec3f(0,1,0),csg_speed*4,0,1,'k');
  commandMap['K'] = new  Commander("Hand3_Rotator",osg::Vec3f(0,1,0),-csg_speed*4,0,1,'K');
  commandMap['j'] = new Commander("Hand2_Rotator",osg::Vec3f(0,0,1),csg_speed*2,90,360,'j');
  commandMap['J'] = new Commander("Hand2_Rotator",osg::Vec3f(0,0,1),-csg_speed*2,90,360,'J');
  commandMap['b'] = new Commander("Body_Rotator",osg::Vec3f(0,0,1),csg_speed*2,90,360,'b');
  commandMap['B'] = new Commander("Body_Rotator",osg::Vec3f(0,0,1),-csg_speed*2,90,360,'B');
  commandMap['h'] = new Commander("Hand1_Rotator",osg::Vec3f(1,0,0),csg_speed,45,360,'h');
  commandMap['H'] = new Commander("Hand1_Rotator",osg::Vec3f(1,0,0),-csg_speed,45,360,'H');
  commandMap['l'] = new Commander("LowerArm_Rotator",osg::Vec3f(1,0,0),csg_speed,45,360,'l');
  commandMap['L'] = new Commander("LowerArm_Rotator",osg::Vec3f(1,0,0),-csg_speed,45,360,'L');
  commandMap['u'] = new Commander("UpperArm_Rotator",osg::Vec3f(1,0,0),csg_speed,35,360,'u');
  commandMap['U'] = new Commander("UpperArm_Rotator",osg::Vec3f(1,0,0),-csg_speed,35,360,'U');
}

RobotUpdator::~RobotUpdator(void){
    
    for (std::map<char, Commander *>::iterator i=commandMap.begin(); i!=commandMap.end(); i++)
      delete i->second;
    commandMap.clear();
    delete onRotCmd;
}

void RobotUpdator::pressKey(char key)
{
    if (!onRotCmd) {
      //  std::cout << key << std::endl;
        onRotCmd = commandMap[key];

    }
    
  /*  std::string nodeName = commandMap[key].nodeName;//namemap[key];
    FindNodeVisitor finder(nodeName);
    robot->accept(finder);
    osg::MatrixTransform* mt = dynamic_cast <osg::MatrixTransform*> (finder.getFirst());
    if(mt){
        osg::Quat qrot = mt->getMatrix().getRotate();
        osg::Vec3f v3f;
        double angle;
        qrot.getRotate(angle, v3f);
        if(osg::RadiansToDegrees(angle)>commandMap[key].minDegree && osg::RadiansToDegrees(angle) < commandMap[key].maxDegree&&commandMap[key].blocked)
         setNodeColor(mt, RED);
        else{
            osg::Matrix mtx = osg::Matrix::rotate(osg::DegreesToRadians(commandMap[key].speed),commandMap[key].axis);
            mt->setMatrix(mt->getMatrix()*mtx);
            //commandMap[commandMap[key].speed > 0?key-32:key+32].blocked = false;
            commandMap[commandMap[key].speed > 0?toupper(key):tolower(key)].blocked = false;
            // std::cout<< commandMap[commandMap[key].speed > 0?toupper(key):tolower(key)].speed<<std::endl;
            commandMap[key].blocked = true;
            setNodeColor(mt,GREEN);
        }

    } */
}
osg::Switch* RobotUpdator::findSwitch(osg::Group *node){
    
    unsigned int num = node->getNumChildren();
    osg::Switch *pSwitch = NULL;
    for( unsigned int i = 0; i < num; i++ )
    {
       // std::cout << node->getChild(i)->className()<<std::endl;
        pSwitch =  dynamic_cast <osg::Switch*> (node->getChild(i));
        if(pSwitch)
            break;
    }
    return pSwitch;
}

void RobotUpdator::updateRotation()
{
    std::string nodeName =  onRotCmd->nodeName;//namemap[key];
    FindNodeVisitor finder(nodeName);
    robot->accept(finder);
    osg::MatrixTransform *mt = dynamic_cast <osg::MatrixTransform *> (finder.getFirst());
    if(mt){
    //    std::cout << nodeName << std::endl;
        
        osg::Switch *pSwitch = findSwitch(mt);
       if (pSwitch) {
         //  std::cout << nodeName<<"===" << std::endl;
        osg::Quat qrot = mt->getMatrix().getRotate();
        osg::Vec3f v3f;
        double angle;
        qrot.getRotate(angle, v3f);
        if(osg::RadiansToDegrees(angle)>onRotCmd->minDegree && osg::RadiansToDegrees(angle) < onRotCmd->maxDegree&&onRotCmd->blocked){
            pSwitch->setAllChildrenOff();
            pSwitch->setSingleChildOn(1);
        }
         //   setNodeColor(mt, RED);
        else{
            osg::Matrix mtx = osg::Matrix::rotate(osg::DegreesToRadians(onRotCmd->speed),onRotCmd->axis);
            mt->setMatrix(mt->getMatrix() * mtx);
            //commandMap[commandMap[key].speed > 0?key-32:key+32].blocked = false;
            commandMap[onRotCmd->speed > 0?toupper(onRotCmd->key):tolower(onRotCmd->key)]->blocked = false;
          //   std::cout<< commandMap[commandMap[onRotCmd->key].speed > 0?toupper(onRotCmd->key):tolower(onRotCmd->key)].speed<<std::endl;
        //    std::cout<<( onRotCmd->key) << std::endl;
            onRotCmd->blocked = true;
         //setNodeColor(mt,GREEN);
            pSwitch->setAllChildrenOff();
            pSwitch->setSingleChildOn(2);
        }
      }
    }
}


void RobotUpdator::releaseKey(char key){
   // std::string nodeName = namemap[key];
    std::string nodeName = commandMap[key]->nodeName;
    FindNodeVisitor finder(nodeName);
    robot->accept(finder);
    osg::MatrixTransform *pMt = dynamic_cast <osg::MatrixTransform *> (finder.getFirst());
    if (pMt) {
     osg::Switch *pSwitch = findSwitch(pMt);
        if (pSwitch) {
            pSwitch->setAllChildrenOff();
            pSwitch->setSingleChildOn(0);
        }
    }
    onRotCmd = NULL;            
}

/*
void RobotUpdator::setGeodeColor( osg::Geode* node, const osg::Vec4& color )
{
    //  std::cout << node->className() << std::endl;
    if( node == 0 ) return;
    
    osg::Material* mat =
    dynamic_cast<osg::Material*>( node->getOrCreateStateSet()->getAttribute( osg::StateAttribute::MATERIAL ) );
    if ( !mat )
    {
        
        mat = new osg::Material();
        
        node->getOrCreateStateSet()->setAttribute(mat, osg::StateAttribute::MATERIAL);
        
    }
    // mat->setDiffuse( osg::Material::FRONT_AND_BACK, color );
    mat->setColorMode(osg::Material::ColorMode::SPECULAR);
    mat->setSpecular(osg::Material::FRONT_AND_BACK, color);
}

void RobotUpdator::setNodeColor( osg::Node* node, const osg::Vec4& newColor )
{
    
    unsigned int numGeoms = node->asGroup()->getNumChildren();
    for( unsigned int geodeIdx = 0; geodeIdx < numGeoms; geodeIdx++ )
    {
      //   std::cout<<"set" << numGeoms << std::endl;
        osg::Geode* ge =  dynamic_cast <osg::Geode*> (node->asGroup()->getChild(geodeIdx));
        if(ge)
          setGeodeColor(ge, newColor );
    }
}

void RobotUpdator::resetNodeColor(osg::Node* node)
{
    unsigned int numGeoms = node->asGroup()->getNumChildren();
     // std::cout << "clear" <<numGeoms  <<std::endl;
    for( unsigned int geodeIdx = 0; geodeIdx < numGeoms; geodeIdx++ ){
       osg::Geode* ge =  dynamic_cast <osg::Geode*> (node->asGroup()->getChild(geodeIdx));
    //    std::cout<<ge<<std::endl;
        if(ge)
            ge->getOrCreateStateSet()->removeAttribute(osg::StateAttribute::MATERIAL);
    }
    
}*/


