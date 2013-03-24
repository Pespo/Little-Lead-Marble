#pragma once
#ifndef INPUTLISTERNER_H
#define INPUTLISTERNER_H

#include <CEGUI.h>
#include <Ogre.h>
#include <OIS/OIS.h>
#include <OgreSceneManager.h>

namespace llm {

	class InputListener : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener {

	protected :
		Ogre::RenderWindow* 	m_pWindow;
		Ogre::Camera*       	m_pCamera;
		Ogre::SceneManager* 	m_pSceneManager;
		Ogre::DefaultRaySceneQuery*	m_pRaySceneQuery;
 
		OIS::InputManager*  m_pInputManager;
		OIS::Mouse*         m_pMouse;
		OIS::Keyboard*      m_pKeyboard;

		bool m_bContinue;
 
		Ogre::Vector3 m_mouvement;
		Ogre::Real m_vitesse;
		Ogre::Real m_vitesseRotation;

		// OgreBites::SdkTrayManager* m_pTrayMgr;

	public:
		/**
		* InputListener
		* @Pespo
		* @param [window] : [Pointer to a render window]
		* @param [camera] : [Pointer to a camera]
		* @param [sceneManager] : [Pointer to a scene manager]
		*/
		InputListener( Ogre::RenderWindow *window );
		~InputListener();
	
		/**
		* frameRenderingQueued
		* @Pespo
		* @param [evt] : [Reference to an ogre frame event]
		* @return [bool] : []
		*/
		bool frameRenderingQueued(const Ogre::FrameEvent& evt);
		void startOIS( Ogre::RenderWindow *window );
		void windowResized( Ogre::RenderWindow *window );
		void windowClosed();
		void quit();
		CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID);
		CEGUI::Key::Scan convertKey(OIS::KeyEvent e);

		bool quit(const CEGUI::EventArgs& e); 

		virtual bool mouseMoved(const OIS::MouseEvent &e);
		virtual bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		virtual bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
		virtual bool keyPressed(const OIS::KeyEvent &e);
		virtual bool keyReleased(const OIS::KeyEvent &e);
	};
}
#endif