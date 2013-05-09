//
//  type.h
//  testlibx
//
//  Created by MayoKaze on 5/8/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef testlibx_type_h
#define testlibx_type_h
#include "RobotUpdator.h"
#include "DraggerSwitch.h"
#include <osg/Texture2D>
#include <osgFX/Scribe>
#include <osgUtil/LineSegmentIntersector>
#include <osgParticle/PrecipitationEffect>
#include <osg/ValueObject>

typedef osg::ref_ptr<osg::Geode> pt_geode;
typedef osg::ref_ptr<osg::Node> pt_node;
typedef osg::ref_ptr<osg::Geometry> pt_geometry;
typedef osg::ref_ptr<osg::DrawElementsUByte> pt_drawElements;
typedef osg::ref_ptr<osg::Vec3Array> pt_vec3arr;
typedef osg::ref_ptr<osg::Vec4Array> pt_vec4arr;
typedef osg::ref_ptr<osg::MatrixTransform> pt_matrixTrans;
typedef osg::ref_ptr<osg::ShapeDrawable> pt_shapeDrawble;
typedef osg::ref_ptr<osg::Texture2D> pt_texture2d;
typedef osg::ref_ptr<RobotUpdator> pt_robotUpdator;
typedef osg::ref_ptr<osg::Group>  pt_group;
typedef osg::ref_ptr<osg::Switch> pt_switch;
typedef osg::ref_ptr<osg::Material> pt_material;
typedef osg::ref_ptr<osg::Group> pt_group;
typedef osg::ref_ptr<osgFX::Scribe> pt_scribe;
typedef osg::ref_ptr<osgUtil::LineSegmentIntersector> pt_lsi;
typedef osg::ref_ptr<osgFX::Scribe>  pt_selectedNode;
typedef osg::ref_ptr<osgParticle::PrecipitationEffect> pt_precipitationEffect;
typedef osg::ref_ptr<DraggerSwitch> pt_dragSwitch;
typedef std::vector<std::string> t_stringlist;
typedef osg::ref_ptr<osg::Node*>  pt_model;

const  float csg_AmbCoef=0.1f;
const  float csg_DiffCoef=0.8f;
const  float csg_SpecCoef=1.0f;
const float csg_speed = 0.5f;
const  osg::Vec4 csg_redv  =   osg::Vec4(1.0f,0.0f,0.0f,1.0f); //{1.0f,0.0f,0.0f,1.0f};
const  osg::Vec4 csg_greenv = osg::Vec4(0.0f,1.0f,0.0f,1.0f); //{0.0f,1.0f,0.0f,1.0f};

#endif
