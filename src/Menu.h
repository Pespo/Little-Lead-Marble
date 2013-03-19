#pragma once
#ifndef MENU_H
#define MENU_H

#include "InputListenerCEGUI.h"
#include <Ogre.h>

	
namespace llm {

	class Menu {

		llm::InputListenerCEGUI* m_pInputListener;
		Ogre::SceneManager* m_pSceneManager;
		Ogre::Camera* m_pCamera;

	public:
		Menu();
		~Menu();

		void loop();

	};
}
#endif