//
//  DeSelectVisitor.h
//  testlibx
//
//  Created by MayoKaze on 5/8/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__DeSelectVisitor__
#define __testlibx__DeSelectVisitor__

#include <iostream>
#include <osg/NodeVisitor>
#include <osgFX/Scribe>
#include "type.h"

class DeSelectVisitor:public osg::NodeVisitor
{
public:
    
    DeSelectVisitor();
    virtual ~DeSelectVisitor();
    virtual void apply(osg::Node& node);
    void deSelectNode();
private:
    pt_selectedNode m_selected;

};

#endif /* defined(__testlibx__DeSelectVisitor__) */
