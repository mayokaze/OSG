//
//  SaveVisitor.h
//  testlibx
//
//  Created by MayoKaze on 5/9/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__SaveVisitor__
#define __testlibx__SaveVisitor__

#include <iostream>
#include <osg/NodeVisitor>
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filestream.h"

using namespace rapidjson;
class SaveVisitor: public osg::NodeVisitor
{
public:
	SaveVisitor(PrettyWriter<FileStream>* w);
	virtual ~SaveVisitor(void);
    virtual void apply(osg::Node& node);
private:
    PrettyWriter<FileStream> *writer;
};
#endif /* defined(__testlibx__SaveVisitor__) */
