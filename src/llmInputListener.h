#ifndef _llmInputListener_H_
#define _llmInputListener_H_

#include <Ogre.h>
#include <OIS/OIS.h>
#include <OgreSceneManager.h>
#include <SdkTrays.h>
 
class llmInputListener : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener, OgreBites::SdkTrayListener {

public:
	llmInputListener(Ogre::RenderWindow *wnd, Ogre::Camera *camera, Ogre::SceneManager *sceneMgr);
	~llmInputListener();
	
	bool frameRenderingQueued(const Ogre::FrameEvent& evt);
	void startOIS();
	void windowResized(Ogre::RenderWindow* wnd);
	void windowClosed(Ogre::RenderWindow* wnd);

	bool mouseMoved(const OIS::MouseEvent &e);
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool keyPressed(const OIS::KeyEvent &e);
	bool keyReleased(const OIS::KeyEvent &e);

private:
    Ogre::RenderWindow* mWindow;
    Ogre::Camera*       mCamera;
	Ogre::SceneManager* mSceneMgr;
 
    OIS::InputManager*  mInputManager;
    OIS::Mouse*         mMouse;
    OIS::Keyboard*      mKeyboard;

    bool mContinuer;
 
    Ogre::Vector3 mMouvement;
    Ogre::Real mVitesse;
    Ogre::Real mVitesseRotation;

    OgreBites::SdkTrayManager* mTrayMgr;
};
#endif