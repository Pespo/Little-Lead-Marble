#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Object.h"

#include <Ogre.h>
#include <btBulletDynamicsCommon.h>
#include <Bullet-C-Api.h>
#include <btBulletCollisionCommon.h>

#include <CEGUI.h>
#include <RendererModules\Ogre\CEGUIOgreRenderer.h>

namespace llm{
 
    class Application {

        //Variable ogre3d
        Ogre::Root *m_pRoot;
        Ogre::RenderWindow* m_pWindow;
        Ogre::Camera* m_pCamera;
        Ogre::SceneManager* m_pSceneMgr;
        Ogre::FrameListener* m_pInputListener;

        CEGUI::OgreRenderer* mRenderer;

        //variable bullet
        btDbvtBroadphase* m_pBroadphase;
        btDefaultCollisionConfiguration* m_pCollisionConfiguration;
        btCollisionDispatcher* m_pDispatcher;
        btSequentialImpulseConstraintSolver* m_pSolver;
        btDiscreteDynamicsWorld* m_pWorld;

        //autre
        std::vector<Object*> m_objectList;
        bool m_bShutDown;

    public:
        Application( );
        ~Application( );
     
        bool start( );
        void exit( );
        bool quit(const CEGUI::EventArgs& e);
        void createFrameListener( );
        
    };

}

#endif