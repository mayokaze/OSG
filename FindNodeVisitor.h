//
//  findNodeVisitor.h
//  testlibx
//
//  Created by MayoKaze on 4/28/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__findNodeVisitor__
#define __testlibx__findNodeVisitor__

#include <osg/Node>
#include <osg/NodeVisitor>
#include <vector>
#include <iostream>
typedef std::vector<osg::Node*> nodeListType;
class FindNodeVisitor : public osg::NodeVisitor
{
public:
    FindNodeVisitor();
    FindNodeVisitor(const std::string &searchName) ;
    
    virtual void apply(osg::Node &searchNode);
   // virtual void apply(osg::Transform &searchNode);
    
    void setNameToFind(const std::string &searchName);
    osg::Node* getFirst();
   
    nodeListType& getNodeList() { return foundNodeList; }
private:
    std::string searchForName;
    nodeListType foundNodeList;
};

#endif /* defined(__testlibx__findNodeVisitor__) */
