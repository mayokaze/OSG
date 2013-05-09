
#include <iostream>

#include "PrintVisitor.h"


PrintVisitor::PrintVisitor(void) : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ACTIVE_CHILDREN)
{
}


PrintVisitor::~PrintVisitor(void)
{
}

void PrintVisitor::apply( osg::Node& node )
{
	for(unsigned int i=0;i<getNodePath().size();i++) std::cout << "|--";
    std::cout << node.className() << " Name: " << node.getName() << " Lib: " << node.libraryName() << std::endl; 
    if(node.getName()!="draggers")
	traverse(node);
}
