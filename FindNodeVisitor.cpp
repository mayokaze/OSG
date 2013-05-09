//
//  findNodeVisitor.cpp
//  testlibx
//
//  Created by MayoKaze on 4/28/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#include "findNodeVisitor.h"



FindNodeVisitor::FindNodeVisitor() : osg::NodeVisitor(TRAVERSE_ALL_CHILDREN),searchForName()
{
}
FindNodeVisitor::FindNodeVisitor(const std::string &searchName):osg::NodeVisitor(TRAVERSE_ALL_CHILDREN),searchForName(searchName)
{
}
void FindNodeVisitor::setNameToFind(const std::string &searchName)
{
    searchForName = searchName;
    foundNodeList.clear();
}
osg::Node* FindNodeVisitor::getFirst()
{
    return *(foundNodeList.begin());
}
void FindNodeVisitor::apply(osg::Node &searchNode)
{
    if (searchNode.getName() == searchForName)
    {
    //    std::cout << searchNode.className() << " Name: " << searchNode.getName() << " Lib: " << searchNode.libraryName() << std::endl;
        foundNodeList.push_back(&searchNode);
    }
    traverse(searchNode);
}
/*void findNodeVisitor::apply(osg::Transform &searchNode)
{
    osgSim::DOFTransform* dofNode =
    dynamic_cast<osgSim::DOFTransform*> (&searchNode);
    if (dofNode)
    {
        dofNode->setAnimationOn(false);
    }
    apply ( (osg::Node&) searchNode);
    traverse(searchNode);
}*/