#pragma once
#ifndef INPUTLISTERNERCEGUI_H
#define INPUTLISTERNERCEGUI_H

#include "InputListener.h"

#include <CEGUI.h>
#include <Ogre.h>
#include <OIS/OIS.h>
#include <OgreSceneManager.h>
// #include <SdkTrays.h>

namespace llm {

	class InputListenerCEGUI : public InputListener {

	public:
		InputListenerCEGUI(Ogre::RenderWindow *window, Ogre::Camera *camera, Ogre::SceneManager *sceneManager);
		CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);

		virtual bool mouseMoved(const OIS::MouseEvent &e);
		virtual bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		virtual bool keyPressed(const OIS::KeyEvent &e);
		virtual bool keyReleased(const OIS::KeyEvent &e);

		void quit();
	};
}
#endif