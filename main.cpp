// raaOSGSimpleDemo.cpp : Defines the entry point for the console application.
//


#include "type.h"
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/SphericalManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osg/MatrixTransform>
#include <osg/Group>
#include <osg/Geode>
#include <osg/StateSet>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <iostream>

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filestream.h"
#include "SimpleEventHandler.h"
#include "PrintVisitor.h"
#include "FindNodeVisitor.h"
#include "RobotUpdator.h"
#include "RobotHandler.h"
#include "InitVisitor.h"
#include "RobotCallback.h"
#include "OSGShape.h"
#include "AddEventHandler.h"
#include "PickerHandler.h"
#include "CameraRecordHandler.h"
#include "OSGFx.h"
#include "FxHandler.h"
#include "DraggerSwitchHandler.h"
#include "FileHandler.h"
#include "InitHelper.h"



//const static float csg_AmbCoef=0.1f;
//const static float csg_DiffCoef=0.8f;
//const static float csg_SpecCoef=1.0f;

/*

void initGC(osgViewer::Viewer* pViewer){
    
    
    std::ifstream in("scene.json", std::ios::in);
    std::istreambuf_iterator<char> beg(in), end;
    std:: string json(beg, end);
    in.close();
    Document doc;
    doc.Parse<0>(json.c_str());
    if (doc.HasParseError())
    {
        printf("GetParseError %s\n",doc.GetParseError());
        return;
    }
    for (Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr){
        if(itr->IsObject()){
            std::string type = (*itr)["type"].GetString();
            if(type == "window"){
                osg::GraphicsContext::Traits *pTraits = new osg::GraphicsContext::Traits();
                pTraits->x = (*itr)["x"].GetInt();
                pTraits->y = (*itr)["y"].GetInt();
                pTraits->width = (*itr)["width"].GetInt();
                pTraits->height = (*itr)["height"].GetInt();
                pTraits->windowDecoration = true;
                pTraits->doubleBuffer = true;
                pTraits->sharedContext = 0;
                osg::GraphicsContext *pGC = osg::GraphicsContext::createGraphicsContext(pTraits);
                //pViewer
                pViewer ->getCamera()->setGraphicsContext(pGC);
                osg::Camera *pCamera = pViewer->getCamera();
                
                pCamera->setGraphicsContext(pGC);
                pCamera->setViewport(new osg::Viewport(0,0, pTraits->width, pTraits->height));
            }
        }}}


*/
using namespace std;
pt_group g_pRoot=0;






#pragma mark
int main(int argc,char* argv[])
{
	//osg::ArgumentParser arguments(&argc,argv);
    std::string path = argv[1];
	g_pRoot= initScene(path);
   // pt_switch s = fx.getScene();
    //manip->addChild(s);
    
	// setup viewer
	osgViewer::Viewer viewer;
    
	// define graphics context
	osg::GraphicsContext::Traits *pTraits = new osg::GraphicsContext::Traits();
	pTraits->x = 20;
	pTraits->y = 20;
	pTraits->width = 600;
	pTraits->height = 480;
	pTraits->windowDecoration = true;
	pTraits->doubleBuffer = true;
	pTraits->sharedContext = 0;
	osg::GraphicsContext *pGC = osg::GraphicsContext::createGraphicsContext(pTraits);
    
	osgGA::KeySwitchMatrixManipulator* pKeyswitchManipulator = new osgGA::KeySwitchMatrixManipulator();
	pKeyswitchManipulator->addMatrixManipulator( '1', "Trackball", new osgGA::TrackballManipulator() );
	pKeyswitchManipulator->addMatrixManipulator( '2', "Flight", new osgGA::FlightManipulator() );
	pKeyswitchManipulator->addMatrixManipulator( '3', "Drive", new osgGA::DriveManipulator() );
    pKeyswitchManipulator->addMatrixManipulator( '4', "Sphererical", new osgGA::SphericalManipulator() );
	viewer.setCameraManipulator(pKeyswitchManipulator);
  // pKeyswitchManipulator->


    osg::Camera *pCamera = viewer.getCamera();
    
	pCamera->setGraphicsContext(pGC);
	pCamera->setViewport(new osg::Viewport(0,0, pTraits->width, pTraits->height));
    
    viewer.addEventHandler(new PickHandler);
    viewer.addEventHandler(new AddEventHandler);
    viewer.addEventHandler(new FXHandler);
    viewer.addEventHandler(new FileHandler);
    // add the stats handler -> press 's'
    viewer.addEventHandler(new osgViewer::StatsHandler);
    viewer.addEventHandler(new CameraRecordHandler);
    viewer.addEventHandler(new DraggerSwitchHandler);
    // RAA::Exercise 3
	// add custom handler -> press 'F1' for info, 'F2' for rendering modes,'F3' for scence saving,'F4' 
	viewer.addEventHandler(new SimpleEventHandler());
    
	// add the thread model handler -> press 'm'
	//viewer.addEventHandler(new osgViewer::ThreadingHandler);
    
	// add the window size toggle handler -> press 'f'
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
    // add the record camera path handler
	//viewer.addEventHandler(new osgViewer::RecordCameraPathHandler);
    
	// add the LOD Scale handler
	//viewer.addEventHandler(new osgViewer::LODScaleHandler);
    
	// add the screen capture handler -> press 'c'. look for image file in working dir($(osg)\bin)
	viewer.addEventHandler(new osgViewer::ScreenCaptureHandler);
    
	// add the help handler -> press 'h'
	//viewer.addEventHandler(new osgViewer::HelpHandler);
 //   viewer.addEventHandler(new RobotHandler);
	// set the scene to render
	viewer.setSceneData(g_pRoot);
    InitVisitor iv = InitVisitor();
    iv.traverse(*(viewer.getScene()->getSceneData()));
	viewer.realize();
    
	return viewer.run();
}

