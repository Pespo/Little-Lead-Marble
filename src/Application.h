#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Object.h"
#include "Singleton.h"
#include "Level.h"

#include <Ogre.h>
#include <btBulletDynamicsCommon.h>
#include <Bullet-C-Api.h>
#include <btBulletCollisionCommon.h>

#include <CEGUI.h>
#include <RendererModules\Ogre\CEGUIOgreRenderer.h>

namespace llm{
 
    class Application : public Singleton<Application> {

		friend class Singleton<Application>;

		Application( );
        ~Application( );

        //Variable ogre3d
        Ogre::Root *m_pRoot;
        Ogre::RenderWindow* m_pWindow;
        CEGUI::OgreRenderer* mRenderer;
        Ogre::Camera* m_pCamera;
        Ogre::SceneManager* m_pSceneManagerLevel;
        Ogre::SceneManager* m_pSceneManagerMenu;
        Ogre::FrameListener* m_pInputListener;

        //variable bullet
        btDbvtBroadphase* m_pBroadphase;
        btDefaultCollisionConfiguration* m_pCollisionConfiguration;
        btCollisionDispatcher* m_pDispatcher;
        btSequentialImpulseConstraintSolver* m_pSolver;
        btDiscreteDynamicsWorld* m_pWorld;

        //autre
        bool m_bShutDown;
        llm::Level* m_pLevel;

    public:
        bool start( );

		inline llm::Level *level() {
			return m_pLevel;
		}
        
        bool quit(const CEGUI::EventArgs& e); 
        inline Ogre::Root* root(){
            return m_pRoot;
        }  
        inline Ogre::RenderWindow* window(){
            return m_pWindow;
        } 
        inline Ogre::SceneManager* sceneManagerLevel(){
            return m_pSceneManagerLevel;
        }  
        inline Ogre::Camera* camera(){
            return m_pCamera;
        } 
		inline btDiscreteDynamicsWorld* world(){
            return m_pWorld;
        } 

    };

}

#endif