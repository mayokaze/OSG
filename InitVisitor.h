//
//  InitVisitor.h
//  testlibx
//
//  Created by MayoKaze on 4/30/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__InitVisitor__
#define __testlibx__InitVisitor__

#include <iostream>
#include <osg/NodeVisitor>


#include "util"

class InitVisitor: public osg::NodeVisitor
{
public:
	InitVisitor(void);
	virtual ~InitVisitor(void);
    virtual void apply(osg::Node& node);
private:
    void setGroupColor( osg::Group* node, const osg::Vec4& color );
    void setNodeColor( osg::Node* node, const osg::Vec4& newColor );

};
#endif /* defined(__testlibx__InitVisitor__) */
