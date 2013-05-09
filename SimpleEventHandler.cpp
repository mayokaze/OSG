

#include <osgViewer/Viewer>
#include <osg/StateSet>
#include <osgDB/WriteFile>

#include "PrintVisitor.h"

#include "SimpleEventHandler.h"


SimpleEventHandler::SimpleEventHandler()
{
	m_mMode=osg::PolygonMode::FILL;
}

SimpleEventHandler::~SimpleEventHandler(void)
{
}

bool SimpleEventHandler::handle( const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor * )
{
	osgViewer::Viewer *pViewer=dynamic_cast<osgViewer::Viewer*>(aa.asView());
	
	if(pViewer && ea.getEventType()==osgGA::GUIEventAdapter::KEYDOWN)
	{	
		switch(ea.getKey())
		{
            case osgGA::GUIEventAdapter::KEY_F1:
            {
                pViewer->home();
                return true;
            }
            case  osgGA::GUIEventAdapter::KEY_F2:
            {
                osgDB::writeNodeFile(*pViewer->getSceneData(), "selected_model.osgt");
                return true;
            }
			case osgGA::GUIEventAdapter::KEY_F3:
            {
				PrintVisitor printer;
                printer.traverse(*(pViewer->getScene()->getSceneData()));
                return true;
			}
			case osgGA::GUIEventAdapter::KEY_F4:
            {
				pViewer->getSceneData()->getOrCreateStateSet()->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, progressMode()), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
				return true;
            }
		}
	}
	return false;
}

osg::PolygonMode::Mode SimpleEventHandler::progressMode()
{
	switch(m_mMode)
	{
		case osg::PolygonMode::POINT:
			return m_mMode=osg::PolygonMode::LINE;
		case osg::PolygonMode::LINE:
			return m_mMode=osg::PolygonMode::FILL;
		default:
			return m_mMode=osg::PolygonMode::POINT;
	}
}
