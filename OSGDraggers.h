//
//  OSGDraggers.h
//  testlibx
//
//  Created by MayoKaze on 5/9/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__OSGDraggers__
#define __testlibx__OSGDraggers__

#include <iostream>
#include <string>
#include <vector>
#include "DraggerSwitch.h"
#include "type.h"

class OSGDraggers
{
public:
    
    OSGDraggers(t_stringlist names);
	virtual ~OSGDraggers(void);
    DraggerSwitch* getScene();
    
private:
    t_stringlist m_names;
};

#endif /* defined(__testlibx__OSGDraggers__) */
