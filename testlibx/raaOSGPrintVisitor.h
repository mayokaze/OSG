#if !defined(_PRINT_)
#define _PRINT_


#include <osg/NodeVisitor>

class raaOSGPrintVisitor: public osg::NodeVisitor
{
public:
	raaOSGPrintVisitor(void);
	virtual ~raaOSGPrintVisitor(void);

	virtual void apply(osg::Node &node);
};
#endif
