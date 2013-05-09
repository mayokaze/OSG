//
//  DeSelectVisitor.cpp
//  testlibx
//
//  Created by MayoKaze on 5/8/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#include "DeSelectVisitor.h"
DeSelectVisitor::DeSelectVisitor():osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN){}

DeSelectVisitor::~DeSelectVisitor(){}



void DeSelectVisitor::apply(osg::Node& node)
{
    pt_scribe scribe = dynamic_cast<osgFX::Scribe*>(&node);
    if (scribe) {
        m_selected = scribe;
    }
    else {
        traverse(node);
    }
}

void DeSelectVisitor::deSelectNode()
{
    if (!m_selected) return;
    osg::Node::ParentList parents = m_selected->getParents();
        for(osg::Node::ParentList::iterator pitr = parents.begin();
            pitr != parents.end();
            ++pitr)
        {
             pt_group parent = *pitr;
             parent->replaceChild(m_selected,m_selected->getChild(0));
        }
    m_selected = NULL;
}