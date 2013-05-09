#define __SHAPE__

#include <osg/ShapeDrawable>

#include <osgViewer/Viewer>
#include <osg/PolygonMode>
#include <osg/StateSet>
#include <osg/Material>
#include <osg/MatrixTransform>
#include <osgdb/ReadFile>
#include <osg/Texture2D>
#include "type.h"

#include "OSGShape.h"
OSGShape::OSGShape(osg::Matrix t,float* c,Kind k):OSGDrawable(t,c),kind(k){}

OSGShape::~OSGShape(){}

osg::Node* OSGShape::makeShape(float scale){
    osg::Node *pNode=0;
    
	if(color)
	{
        //  std::cout<<"testmk"<<std::endl;
		pt_geode pGeode=new osg::Geode();
        pGeode->setUserValue("scale", scale);
        pt_shapeDrawble pGeom = NULL;//Auto release
        std::string ts;
        switch (kind) {
            case sphere:{
                ts = "sphere";
                pGeode->setUserValue("kind",ts);
                pGeom =new osg::ShapeDrawable(new osg::Sphere(osg::Vec3f(0.0f, 0.0f, 0.0f), scale*0.7));
                //Smart pointer test code. Uncomment to see refcount change.
             /*  osg::ShapeDrawable *sd = pGeom;
               std::cout <<    sd->referenceCount()<<std::endl;
                sd->ref();
                std::cout <<    sd->referenceCount()<<std::endl;
                pGeom = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3f(0.0f, 0.0f, 0.0f), scale));
                std::cout <<    sd->referenceCount()<<std::endl;*/
                break;
            }
            case cone:
                ts = "cone";
                pGeode->setUserValue("kind",ts);
                pGeom = new osg::ShapeDrawable(new osg::Cone(osg::Vec3f(0.0f, 0.0f, 0.0f),scale/2,scale));
                break;
            case capsule:
                ts = "capsule";
                pGeode->setUserValue("kind",ts);
                pGeom = new osg::ShapeDrawable(new osg::Capsule(osg::Vec3f(0.0f, 0.0f, 0.0f),scale/2,scale));
                //new osg::Capsule(osg::Vec3(8.0f,0.0f,0.0f),radius,height*2)
                break;
            case texture:{
                ts = "texture";
                pGeode->setUserValue("kind",ts);
                pGeom =new osg::ShapeDrawable(new osg::Sphere(osg::Vec3f(0.0f, 0.0f, 0.0f), scale*0.7));
                osg::StateSet *ss = pGeode->getOrCreateStateSet();
                osg::Image* image = osgDB::readImageFile( "reflect.rgb" );
                if (image)
                {
                    pt_texture2d texture = new osg::Texture2D;
                    texture->setImage(image);
                    texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::NEAREST_MIPMAP_NEAREST);
                    ss->setTextureAttributeAndModes(0,texture, osg::StateAttribute::ON);
                }
                
                ss->setMode(GL_LIGHTING, osg::StateAttribute::ON);
                
                break;
            }
            default:
                return NULL;
        }
		
		
        
        pGeode->addDrawable(pGeom);
        

        
		pt_material pMat=new osg::Material();
        
		pMat->setAmbient(osg::Material::FRONT, osg::Vec4(color[0]*csg_AmbCoef, color[1]*csg_AmbCoef, color[2]*csg_AmbCoef, color[3]));
		pMat->setDiffuse(osg::Material::FRONT, osg::Vec4(color[0]*csg_DiffCoef, color[1]*csg_DiffCoef, color[2]*csg_DiffCoef, color[3]));
		pMat->setSpecular(osg::Material::FRONT, osg::Vec4(color[0]*csg_SpecCoef, color[1]*csg_SpecCoef, color[2]*csg_SpecCoef, color[3]));
		pMat->setShininess(osg::Material::FRONT, 2.0f);
        
		pGeode->getOrCreateStateSet()->setAttributeAndModes(pMat, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
		pGeom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
        
		pNode=pGeode.release();//reference count matained by outsider container
	}
    
	return pNode;
}


osg::MatrixTransform* OSGShape::getScene(float scale){
    pt_matrixTrans ret = new osg::MatrixTransform();
    ret->setName("prim");
    ret->setMatrix(trans);
    ret->addChild(makeShape(scale));
    return ret.release();//reference count matained by outsider container
}
