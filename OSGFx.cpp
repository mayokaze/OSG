//
//  OSGFx.cpp
//  testlibx
//
//  Created by MayoKaze on 5/8/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#include "OSGFx.h"
#include "type.h"

OSGFx::OSGFx(){}
OSGFx::~OSGFx(){}
osg::Switch* OSGFx::getScene(){
    pt_precipitationEffect pfx = new osgParticle::PrecipitationEffect;
    pfx->snow(0.5);
    pfx->setParticleColor(osg::Vec4(1, 1, 1, 1));
    pfx->setWind(osg::Vec3(2, 0, 0));
    pt_switch pSwitch = new osg::Switch;
    pSwitch->setName("fx");
    pSwitch ->addChild(pfx);
    pSwitch ->setAllChildrenOff();
    return pSwitch.release();
}

/*
 osgViewer::Viewer viewer;
 
 osg::ref_ptr<osgParticle::PrecipitationEffect> precipitationEffect = new osgParticle::PrecipitationEffect;
 precipitationEffect->snow(0.5);
 precipitationEffect->setParticleColor(osg::Vec4(1, 1, 1, 1));
 precipitationEffect->setWind(osg::Vec3(2, 0, 0));
 
 osg::Group * root = new osg::Group() ;
 root ->addChild(precipitationEffect.get ()) ;
 osg::Node* ceep = osgDB::readNodeFile("ceep.ive") ;
 root ->addChild(ceep) ;
 
 viewer.setSceneData(root);
 viewer.realize();
 viewer.run();
 return 0;*/