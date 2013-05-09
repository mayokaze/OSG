#if !defined(_EVENT_)
#define _EVENT_

#include <osg/PolygonMode>
#include <osgGA/GUIEventHandler>

class SimpleEventHandler: public osgGA::GUIEventHandler
{
public:
	SimpleEventHandler();
	virtual ~SimpleEventHandler(void);

	virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa, osg::Object *, osg::NodeVisitor *);

protected:
	osg::PolygonMode::Mode m_mMode;

	osg::PolygonMode::Mode progressMode();

};

#endif