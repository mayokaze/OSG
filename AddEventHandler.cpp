//
//  AddEventHandler.cpp
//  testlibx
//
//  Created by MayoKaze on 5/8/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#include "AddEventHandler.h"
#include <osgViewer/Viewer>
#include <osgGA/CameraManipulator>
#include <osg/vec3>
#include "OSGShape.h"
#include "OSGGeometry.h"
#include <iostream>

AddEventHandler::AddEventHandler()
{
	
}

AddEventHandler::~AddEventHandler(void)
{
}

bool AddEventHandler::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa, osg::Object*, osg::NodeVisitor*)
{
	osgViewer::Viewer *pViewer=dynamic_cast<osgViewer::Viewer*>(aa.asView());
	
	if(pViewer && ea.getEventType()==osgGA::GUIEventAdapter::KEYDOWN)
	{
        osg::Vec3 eye, at, up,front,side;
        pViewer->getCameraManipulator()->getInverseMatrix().getLookAt(eye, at, up);
        front= at - eye;
        front.normalize();
        side = front ^ up;
        osg::Matrixf rot,pos,trans;
        rot.makeRotate(eye,at);
        pos.makeTranslate(eye);
        trans.makeTranslate(front*50);
		switch(ea.getKey())
		{
                
            case osgGA::GUIEventAdapter::KEY_Q:
            
            {
              // m3 = m3*m;
                OSGShape s =  OSGShape(trans*rot*pos, NULL,OSGShape::sphere);
                pViewer->getSceneData()->asGroup()->addChild(s.getScene());
              //  
                
                
               /* osg::Matrixf m,m2,m3,m4;
                m = pViewer->getCameraManipulator()->getMatrix();
                osg::Quat qrot = m.getRotate();
                m2.makeRotate(qrot);

                m3.makeTranslate(0, 10, 0);
                osg::Vec3d ts  = m.getTrans();
                m4.makeTranslate(ts);
                OSGShape *s = new OSGShape(m3*m2*m4, NULL,OSGShape::box);
                pViewer->getSceneData()->asGroup()->addChild(s->getScene());*/
                return true;
            }
            case  osgGA::GUIEventAdapter::KEY_A:
            {
                OSGShape s =  OSGShape(trans*rot*pos, NULL,OSGShape::cone);
              //   std::cout <<"test"<<std::endl;
                
                pViewer->getSceneData()->asGroup()->addChild(s.getScene());
            
                return true;
            }
			case osgGA::GUIEventAdapter::KEY_Z:
            {
                OSGShape s =  OSGShape(trans*rot*pos, NULL,OSGShape::capsule);
                pViewer->getSceneData()->asGroup()->addChild(s.getScene());

                return true;
			}
			case osgGA::GUIEventAdapter::KEY_X:
            {
                OSGGeometry g = OSGGeometry(trans*rot*pos, NULL,OSGGeometry::light);
                pViewer->getSceneData()->asGroup()->addChild(g.getScene());
            
				return true;
            }
            case osgGA::GUIEventAdapter::KEY_W:
            {
                OSGGeometry g = OSGGeometry(trans*rot*pos, NULL,OSGGeometry::pure);
                pViewer->getSceneData()->asGroup()->addChild(g.getScene());
                
				return true;
            }
            case osgGA::GUIEventAdapter::KEY_E:
            {
               // OSGGeometry g = OSGGeometry(trans*rot*pos, NULL,OSGGeometry::texture);
                OSGShape s =  OSGShape(trans*rot*pos, NULL,OSGShape::texture);
               
                pViewer->getSceneData()->asGroup()->addChild(s.getScene());
                
				return true;
            }
          /*  case osgGA::GUIEventAdapter::KEY_R:
            {
                 OSGGeometry g = OSGGeometry(trans*rot*pos, NULL,OSGGeometry::texture);
                //OSGShape s =  OSGShape(trans*rot*pos, NULL,OSGShape::texture);
                pViewer->getSceneData()->asGroup()->addChild(g.getScene());
                
				return true;
            }*/
		}
	}
	return false;
}