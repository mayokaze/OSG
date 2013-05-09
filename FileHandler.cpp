//
//  FileHandler.cpp
//  testlibx
//
//  Created by MayoKaze on 5/9/13.
//  Copyright (c) 2013 MayoKaze. All rights reserved.
//
#define _FILENAME_ "scene.json"

#include <osgViewer/Viewer>
#include <cstdio>
#include <fstream>
#include "FileHandler.h"
#include "SaveVisitor.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/filestream.h"
#include "type.h"
#include "InitHelper.h"
#include "OSGShape.h"
#include "OSGGeometry.h"
#include "InitVisitor.h"
#include "FindNodeVisitor.h"

using namespace rapidjson;

FileHandler::FileHandler(){}

FileHandler::~FileHandler(){}


bool FileHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa){
    if(osgViewer::Viewer *pViewer=dynamic_cast<osgViewer::Viewer*>(aa.asView())){
        if(ea.getEventType()==osgGA::GUIEventAdapter::KEYDOWN&&ea.getKey()==osgGA::GUIEventAdapter::KEY_F5){
            const osg::GraphicsContext::Traits *pTraits = pViewer->getCamera()->getGraphicsContext()->getTraits();
            //std::ofstream file("scene.json",std::ios::out|std::ios::ate);
            FILE *out = fopen(_FILENAME_, "w");
            FileStream sout(out);
            PrettyWriter<FileStream> writer(sout);
            writer.StartArray();
            writer.StartObject();
            writer.String("type");
            writer.String("window");
            writer.String("x");
            writer.Uint(pTraits->x);
            writer.String("y");
            writer.Uint(pTraits->y);
            writer.String("width");
            writer.Uint(pTraits->width);
            writer.String("height");
            writer.Uint(pTraits->height);
            writer.EndObject();
            SaveVisitor sv(&writer);
            pViewer->getSceneData()->accept(sv);
            writer.EndArray();
            fclose(out);
            return true;
        }
        else if(ea.getEventType()==osgGA::GUIEventAdapter::KEYDOWN&&ea.getKey()==osgGA::GUIEventAdapter::KEY_F6){
            std::ifstream in("scene.json", std::ios::in);
            std::istreambuf_iterator<char> beg(in), end;
            std:: string json(beg, end);
            in.close();
            Document doc;
            doc.Parse<0>(json.c_str());
            if (doc.HasParseError())
            {
                printf("GetParseError %s\n",doc.GetParseError());
                return true;
            }
            pt_group root = 0;
            
            
            for (Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr){
                if(itr->IsObject()){
                    std::string type = (*itr)["type"].GetString();
                    float scale;
                    osg::Quat quat;
                    osg::Vec3d trans;
                    osg::Vec3d scalev;
                    float color[4];
                    if(type == "model"){
                        std::string path = (*itr)["path"].GetString();
                        root =  initScene(path);
                        
                    }
                    else if(type == "Body_Rotator"||type == "UpperArm_Rotator"||type == "LowerArm_Rotator"||type == "Hand1_Rotator"||type == "Hand2_Rotator"||type == "Hand3_Rotator"){
                        FindNodeVisitor fv(type);
                        root->accept(fv);
                        pt_matrixTrans mt = dynamic_cast<osg::MatrixTransform*>(fv.getFirst()) ;
                        osg::Matrix m;
                        int c = 0;
                        if((*itr)["quat"].IsArray()){
                            c=0;
                            for (Value::ConstValueIterator i = (*itr)["quat"].Begin(); i != (*itr)["quat"].End(); ++i){
                                quat[c]= i->GetDouble();
                                c++;
                            }
                        }
                        m.makeRotate(quat);
                        mt->setMatrix(mt->getMatrix()*m);
                    
                    }
                    else if(type == "sphere"||type == "cone"||type == "capsule"||type == "capsule"||type == "texture"||type == "lgeo"||type == "lgeo"){
                        scale = (*itr)["scale"].GetDouble();
                        //      Value quat =  (*itr)["quat"];
                         int c = 0;
                        if((*itr)["quat"].IsArray()){
                            
                            for (Value::ConstValueIterator i = (*itr)["quat"].Begin(); i != (*itr)["quat"].End(); ++i){
                                quat[c]= i->GetDouble();
                                c++;
                            }
                        }
                           c=0;
                            for (Value::ConstValueIterator i = (*itr)["scalev"].Begin(); i != (*itr)["scalev"].End(); ++i){
                                scalev[c]= i->GetDouble();
                                c++;
                            }
                            c=0;
                            for (Value::ConstValueIterator i = (*itr)["trans"].Begin(); i != (*itr)["trans"].End(); ++i){
                                trans[c]= i->GetDouble();
                                c++;
                            }
                            if((*itr)["color"].IsArray()){
                              c = 0;
                                for (Value::ConstValueIterator i = (*itr)["color"].Begin(); i != (*itr)["color"].End(); ++i){
                                    color[c]= i->GetDouble();
                                    c++;
                                }
                            }
                            
                            osg::Matrix m1,m2,m3;
                            m1.makeScale(scalev);
                            m2.makeTranslate(trans);
                            m3.makeRotate(quat);
                            
                            if(type=="sphere"){
                                OSGShape sphere(m3*m2*m1,color,OSGShape::sphere);
                                // OSGShape::OSGShape(osg::Matrix t,float* c,Kind k)
                                root->getChild(0)->asGroup()->addChild(sphere.getScene(scale));
                            }
                            else if(type == "cone"){
                                OSGShape cone(m3*m2*m1,color,OSGShape::cone);
                                // OSGShape::OSGShape(osg::Matrix t,float* c,Kind k)
                                root->getChild(0)->asGroup()->addChild(cone.getScene(scale));
                            }
                            else if(type == "capsule"){
                                OSGShape capsule(m3*m2*m1,color,OSGShape::capsule);
                                // OSGShape::OSGShape(osg::Matrix t,float* c,Kind k)
                                root->getChild(0)->asGroup()->addChild(capsule.getScene(scale));
                            }
                            else if(type == "texture"){
                                OSGShape texture(m3*m2*m1,color,OSGShape::texture);
                                // OSGShape::OSGShape(osg::Matrix t,float* c,Kind k)
                                root->getChild(0)->asGroup()->addChild(texture.getScene(scale));
                            }
                            else if(type == "lgeo"){
                                OSGGeometry lgeo(m3*m2*m1,color,OSGGeometry::pure);
                                // OSGShape::OSGShape(osg::Matrix t,float* c,Kind k)
                                root->getChild(0)->asGroup()->addChild(lgeo.getScene(scale));
                            }
                            else if(type == "cgeo"){
                                OSGGeometry cgeo(m3*m2*m1,color,OSGGeometry::light);
                                // OSGShape::OSGShape(osg::Matrix t,float* c,Kind k)
                                root->getChild(0)->asGroup()->addChild(cgeo.getScene(scale));
                            }
                    
                        }
                    }
                }
            InitVisitor iv;
            root->accept(iv);
            pViewer ->setSceneData(root);
            pViewer->run();
            return true;
        }
        
        
    }
    return false;
}
