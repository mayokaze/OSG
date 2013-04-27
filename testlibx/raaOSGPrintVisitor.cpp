
#include <iostream>

#include "raaOSGPrintVisitor.h"


raaOSGPrintVisitor::raaOSGPrintVisitor(void) : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN)
{
}


raaOSGPrintVisitor::~raaOSGPrintVisitor(void)
{
}

void raaOSGPrintVisitor::apply( osg::Node &node )
{
	for(unsigned int i=0;i<getNodePath().size();i++) std::cout << "|--";

	std::cout << node.className() << " Name: " << node.getName() << " Lib: " << node.libraryName() << std::endl; 

	traverse(node);
}
