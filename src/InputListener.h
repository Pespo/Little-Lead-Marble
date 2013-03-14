#pragma once
#ifndef INPUTLISTERNER_H
#define INPUTLISTERNER_H

#include <Ogre.h>
#include <OIS/OIS.h>
#include <OgreSceneManager.h>
#include <SdkTrays.h>

namespace llm {

	class InputListener : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener {

		Ogre::RenderWindow* m_pWindow;
		Ogre::Camera*       m_pCamera;
		Ogre::SceneManager* m_pSceneManager;
 
		OIS::InputManager*  m_pInputManager;
		OIS::Mouse*         m_pMouse;
		OIS::Keyboard*      m_pKeyboard;

		bool m_bContinue;
 
		Ogre::Vector3 m_mouvement;
		Ogre::Real m_vitesse;
		Ogre::Real m_vitesseRotation;

		OgreBites::SdkTrayManager* m_pTrayMgr;

	public:
		/**
		* InputListener
		* @Pespo
		* @param [window] : [Pointer to a render window]
		* @param [camera] : [Pointer to a camera]
		* @param [sceneManager] : [Pointer to a scene manager]
		*/
		InputListener(Ogre::RenderWindow *window, Ogre::Camera *camera, Ogre::SceneManager *sceneManager);
		~InputListener( );
	
		/**
		* frameRenderingQueued
		* @Pespo
		* @param [evt] : [Reference to an ogre frame event]
		* @return [bool] : []
		*/
		bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		void startOIS( );
		void windowResized(Ogre::RenderWindow* window);
		void windowClosed(Ogre::RenderWindow* window);

		bool mouseMoved(const OIS::MouseEvent &e);
		bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		bool keyPressed(const OIS::KeyEvent &e);
		bool keyReleased(const OIS::KeyEvent &e);
	};
}
#endif