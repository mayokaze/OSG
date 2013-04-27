

#include <osgViewer/Viewer>
#include <osg/StateSet>

#include "raaOSGPrintVisitor.h"

#include "raaOSGSimpleEventHandler.h"


raaOSGSimpleEventHandler::raaOSGSimpleEventHandler()
{
	m_mMode=osg::PolygonMode::FILL;
}

raaOSGSimpleEventHandler::~raaOSGSimpleEventHandler(void)
{
}

bool raaOSGSimpleEventHandler::handle( const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor * )
{
	osgViewer::Viewer *pViewer=dynamic_cast<osgViewer::Viewer*>(aa.asView());
	
	if(pViewer && ea.getEventType()==osgGA::GUIEventAdapter::KEYDOWN)
	{	
		switch(ea.getKey())
		{
			case 'i':
			case 'I':
			{
				raaOSGPrintVisitor printer;

				printer.traverse(*(pViewer->getScene()->getSceneData()));
			}
			return true;
			case 'p':
			case 'P':
				pViewer->getSceneData()->getOrCreateStateSet()->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, progressMode()), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);
				return true;
		}
	}
	return false;
}

osg::PolygonMode::Mode raaOSGSimpleEventHandler::progressMode()
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
