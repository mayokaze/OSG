#if !defined(_PRINT_)
#define _PRINT_


#include <osg/NodeVisitor>

class PrintVisitor: public osg::NodeVisitor
{
public:
	PrintVisitor(void);
	virtual ~PrintVisitor(void);

	virtual void apply(osg::Node& node);
};
#endif
