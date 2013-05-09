//
//  DraggerSwitch.h
//  testlibx
//
//  Created by MayoKaze on 5/9/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//

#ifndef __testlibx__DraggerSwitch__
#define __testlibx__DraggerSwitch__

#include <iostream>
#include <osg/Switch>
#include <osgManipulator/Dragger>
#include <osg/MatrixTransform>
class DraggerSwitch: public osg::Switch
{
private:
    //bool m_active;
    int m_index;
    void removeTrans();
public:
	DraggerSwitch(void);
	virtual ~DraggerSwitch(void);
    inline bool isActive(){return m_index == -1;};
    inline int currentIndex(){return m_index;};
    inline  osgManipulator::Dragger* currentDragger(){return m_index == -1? NULL:dynamic_cast<osgManipulator::Dragger*>(getChild(m_index));};
    int nextDragger(osg::MatrixTransform* mt,float scale);
    void disable();
};
#endif /* defined(__testlibx__DraggerSwitch__) */
