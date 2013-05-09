//
//  OSGVertex.cpp
//  testlibx
//
//  Created by MayoKaze on 5/8/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#include "OSGGeometry.h"
#include <osg/ShapeDrawable>

#include <osgViewer/Viewer>
#include <osg/PolygonMode>
#include <osg/StateAttribute>
#include <osg/Material>
#include <osg/MatrixTransform>
#include <osg/Texture2D>
#include <osg/TexEnv>
#include <osgDB/readfile>
#include "type.h"

OSGGeometry::OSGGeometry(osg::Matrix t,float* c,Kind k):OSGDrawable(t,c),kind(k){}

OSGGeometry::~OSGGeometry(){}

osg::Node* OSGGeometry::makeGeo(float scale){
    osg::Node *pNode=0;
    
	if(color)
	{
        pt_geode pGeode=new osg::Geode();
        pGeode->setUserValue("scale", scale);
        pt_geometry pGeom=new osg::Geometry();//auto release
        
        pGeode->addDrawable(pGeom);
        float fHalscale=scale*0.5f;
        pt_vec3arr pVerts=new osg::Vec3Array();
        pVerts->push_back(osg::Vec3(-fHalscale, -fHalscale, -fHalscale));
        pVerts->push_back(osg::Vec3(-fHalscale, fHalscale, -fHalscale));
        pVerts->push_back(osg::Vec3(fHalscale, fHalscale, -fHalscale));
        pVerts->push_back(osg::Vec3(fHalscale, -fHalscale, -fHalscale));
        
        pVerts->push_back(osg::Vec3(-fHalscale, -fHalscale, fHalscale));
        pVerts->push_back(osg::Vec3(fHalscale, -fHalscale, fHalscale));
        pVerts->push_back(osg::Vec3(fHalscale, fHalscale, fHalscale));
        pVerts->push_back(osg::Vec3(-fHalscale, fHalscale, fHalscale));
        
        pGeom->setVertexArray(pVerts);
        
        pt_drawElements pIndex=new osg::DrawElementsUByte(osg::PrimitiveSet::QUADS, 4);
        
        pIndex->push_back(0);
        pIndex->push_back(1);
        pIndex->push_back(2);
        pIndex->push_back(3);
        
        pIndex->push_back(0);
        pIndex->push_back(3);
        pIndex->push_back(5);
        pIndex->push_back(4);
        
        pIndex->push_back(3);
        pIndex->push_back(2);
        pIndex->push_back(6);
        pIndex->push_back(5);
        
        pIndex->push_back(2);
        pIndex->push_back(1);
        pIndex->push_back(7);
        pIndex->push_back(6);
        
        pIndex->push_back(1);
        pIndex->push_back(0);
        pIndex->push_back(4);
        pIndex->push_back(7);
        
        pIndex->push_back(4);
        pIndex->push_back(5);
        pIndex->push_back(6);
        pIndex->push_back(7);
        
        pGeom->addPrimitiveSet(pIndex);
        
        pt_vec3arr pNorms=new osg::Vec3Array();
        pNorms->push_back(osg::Vec3(0.0f, 0.0f, -1.0f));
        pNorms->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
        pNorms->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
        pNorms->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));
        pNorms->push_back(osg::Vec3(-1.0f, 0.0f, 0.0f));
        pNorms->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
        
        pGeom->setNormalArray(pNorms);
        pGeom->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE);
        
        pt_vec4arr pCols=new osg::Vec4Array();
        
        switch (kind) {
            case pure:{
                //disable lighting
                std::string ts = "cgeo";
                pGeode->setUserValue("kind",ts);
                pCols->push_back(osg::Vec4(color[0],color[1],color[2],color[3]));
                pGeom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
                pGeom->setColorArray(pCols);
                pGeom->setColorBinding(osg::Geometry::BIND_OVERALL);
                pt_material pMat=new osg::Material();
              //  pMat->setAmbient(osg::Material::FRONT, osg::Vec4(color[0]*csg_AmbCoef, color[1]*csg_AmbCoef, color[2]*csg_AmbCoef, color[3]));
               // pMat->setDiffuse(osg::Material::FRONT, osg::Vec4(color[0]*csg_DiffCoef, color[1]*csg_DiffCoef, color[2]*csg_DiffCoef, color[3]));
                pMat->setSpecular(osg::Material::FRONT, osg::Vec4(color[0]*csg_SpecCoef, color[1]*csg_SpecCoef, color[2]*csg_SpecCoef, color[3]));
              //  pMat->setShininess(osg::Material::FRONT, 2.0f);
                pGeode->getOrCreateStateSet()->setAttributeAndModes(pMat, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
               // pGeom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
                break;
            }
            case light:{
                //enable lighting
                std::string ts = "lgeo";
                pGeode->setUserValue("kind",ts);
                pCols->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
                pt_material pMat=new osg::Material();
                pMat->setAmbient(osg::Material::FRONT, osg::Vec4(color[0]*csg_AmbCoef, color[1]*csg_AmbCoef, color[2]*csg_AmbCoef, color[3]));
                pMat->setDiffuse(osg::Material::FRONT, osg::Vec4(color[0]*csg_DiffCoef, color[1]*csg_DiffCoef, color[2]*csg_DiffCoef, color[3]));
                pMat->setSpecular(osg::Material::FRONT, osg::Vec4(color[0]*csg_SpecCoef, color[1]*csg_SpecCoef, color[2]*csg_SpecCoef, color[3]));
                pMat->setShininess(osg::Material::FRONT, 2.0f);
                pGeode->getOrCreateStateSet()->setAttributeAndModes(pMat, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
                pGeom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
                pGeom->setColorArray(pCols);
                pGeom->setColorBinding(osg::Geometry::BIND_OVERALL);
               // pt_material pMat=new osg::Material();
                
           
                break;
            }
            /*case texture:{
   
               
                osg::StateSet *ss = pGeom->getOrCreateStateSet();
                osg::Image* image = osgDB::readImageFile( "reflect.rgb" );
                if (image)
                {
                    osg::Texture2D* texture = new osg::Texture2D;
                    texture->setImage(image);
                    texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::NEAREST_MIPMAP_NEAREST);
                    ss->setTextureAttributeAndModes(0,texture, osg::StateAttribute::ON);
                }
                
                ss->setMode(GL_LIGHTING, osg::StateAttribute::ON);
                break;}*/
            default:
                return pNode;
        }
    
     return pGeode.release();
     }
     return pNode;
}


osg::MatrixTransform* OSGGeometry::getScene(float scale){
    pt_matrixTrans ret = new osg::MatrixTransform();
    ret->setName("prim");
   // ret->setUserData(color);
    ret->setMatrix(trans);
    ret->addChild(makeGeo(scale));
    return ret.release();
}
/*osg::Node* makeBox(float scale)
{
	// make a vertex based shape
	osg::Geode *pGeode=new osg::Geode();
	osg::Geometry *pGeom=new osg::Geometry();
    
	pGeode->addDrawable(pGeom);
    
	pGeom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
    float fHalscale=scale*0.5f;
    
	osg::Vec3Array *pVerts=new osg::Vec3Array();
	pVerts->push_back(osg::Vec3(-fHalscale, -fHalscale, -fHalscale));
	pVerts->push_back(osg::Vec3(-fHalscale, fHalscale, -fHalscale));
	pVerts->push_back(osg::Vec3(fHalscale, fHalscale, -fHalscale));
	pVerts->push_back(osg::Vec3(fHalscale, -fHalscale, -fHalscale));
    
	pVerts->push_back(osg::Vec3(-fHalscale, -fHalscale, fHalscale));
	pVerts->push_back(osg::Vec3(fHalscale, -fHalscale, fHalscale));
	pVerts->push_back(osg::Vec3(fHalscale, fHalscale, fHalscale));
	pVerts->push_back(osg::Vec3(-fHalscale, fHalscale, fHalscale));
    
	pGeom->setVertexArray(pVerts);
    
	osg::DrawElementsUByte *pIndex=new osg::DrawElementsUByte(osg::PrimitiveSet::QUADS, 4);
    
	pIndex->push_back(0);
	pIndex->push_back(1);
	pIndex->push_back(2);
	pIndex->push_back(3);
    
	pIndex->push_back(0);
	pIndex->push_back(3);
	pIndex->push_back(5);
	pIndex->push_back(4);
    
	pIndex->push_back(3);
	pIndex->push_back(2);
	pIndex->push_back(6);
	pIndex->push_back(5);
    
	pIndex->push_back(2);
	pIndex->push_back(1);
	pIndex->push_back(7);
	pIndex->push_back(6);
    
	pIndex->push_back(1);
	pIndex->push_back(0);
	pIndex->push_back(4);
	pIndex->push_back(7);
    
	pIndex->push_back(4);
	pIndex->push_back(5);
	pIndex->push_back(6);
	pIndex->push_back(7);
    
	pGeom->addPrimitiveSet(pIndex);
    
	osg::Vec3Array *pNorms=new osg::Vec3Array();
	pNorms->push_back(osg::Vec3(0.0f, 0.0f, -1.0f));
	pNorms->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	pNorms->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	pNorms->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));
	pNorms->push_back(osg::Vec3(-1.0f, 0.0f, 0.0f));
	pNorms->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
    
	pGeom->setNormalArray(pNorms);
	pGeom->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE);
    
	osg::Vec4Array *pCols=new osg::Vec4Array();
	pCols->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	pCols->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	pCols->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	pCols->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
	pCols->push_back(osg::Vec4(1.0f, 0.0f, 1.0f, 1.0f));
	pCols->push_back(osg::Vec4(0.0f, 1.0f, 1.0f, 1.0f));
	pCols->push_back(osg::Vec4(1.0f, 1.0f, 1.0f, 1.0f));
	pCols->push_back(osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f));
    
	pGeom->setColorArray(pCols);
	pGeom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
    
	return pGeode;
}*/