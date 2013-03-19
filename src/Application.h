#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Object.h"
#include "Singleton.h"
#include "Game.h"
#include "Menu.h"

#include <Ogre.h>

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
        Ogre::FrameListener* m_pInputListener;
        //CEGUI::OgreRenderer* m_pRenderer;

        //autre
        bool m_bInGame;

        llm::Game* m_pGame;
        llm::Menu* m_pMenu;

        //Fonction d'initialisation
        void llm::Application::loadRessource();

    public:
        bool start( );

        void setupViewport(Ogre::SceneManager* current, Ogre::String& cameraName);

        bool quit(const CEGUI::EventArgs& e); 
        bool quit(); 
        
        bool pause(const CEGUI::EventArgs &e);
        void pause();

        inline Ogre::Root* root(){
            return m_pRoot;
        }  

        inline Ogre::RenderWindow* window(){
            return m_pWindow;
        }  
        inline Game* game(){
            return m_pGame;
        }
        inline bool inGame() {
            return m_bInGame;
        }
       /* inline llm::Menu* menu(){
            return m_pMenu;
        } */

    };

}

#endif