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

		void pauseMenu();
		void startMenu(bool visible);
		void levelMenu();

	};
}
#endif