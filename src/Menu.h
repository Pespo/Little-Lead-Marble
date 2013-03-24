#pragma once
#ifndef MENU_H
#define MENU_H

#include <Ogre.h>
	
namespace llm {

	class Menu {

		Ogre::SceneManager* m_pSceneManager;
		Ogre::Camera* m_pCamera;

	public:
		Menu();
		~Menu();

		void desactive();
		void startMenu( bool visible );
		void pauseMenu( bool visible );
		
		inline Ogre::SceneManager* sceneManager() { return m_pSceneManager; } 
		inline Ogre::Camera* camera() { return m_pCamera; } 
	};
}
#endif