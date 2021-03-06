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

enum viewport {
    GAME, MENU
};

namespace llm{
 
    class Application : public Singleton<Application> {

		friend class Singleton<Application>;

		Application();
        ~Application();

        //Variable ogre3d
        Ogre::Root *m_pRoot;
        Ogre::RenderWindow* m_pWindow;
        Ogre::FrameListener* m_pInputListener;

        //autre
        bool m_bInGame;

        llm::Game* m_pGame;
        llm::Menu* m_pMenu;

        //Fonction d'initialisation
        void llm::Application::loadRessource();

    public:
        bool start();

        void setupViewport(viewport v);

        bool startGame(const CEGUI::EventArgs& e); 
        void startGame(); 

        bool quit(const CEGUI::EventArgs& e); 
        bool quit(); 
        
        bool pause(const CEGUI::EventArgs &e);
        void pause();

        bool reset(const CEGUI::EventArgs &e);
        void reset();

        inline Ogre::Root* root() { return m_pRoot; } 
        inline Ogre::RenderWindow* window() { return m_pWindow; }
        inline Game* game() { return m_pGame; }
        inline bool inGame() { return m_bInGame; }
        inline Menu* menu() { return m_pMenu; }

    };

}

#endif