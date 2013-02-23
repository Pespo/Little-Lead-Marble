#include <Ogre.h>
#include <OIS/OIS.h>
#include <OgreSceneManager.h>
 
class InputListener : public Ogre::FrameListener, public Ogre::WindowEventListener, public OIS::KeyListener, public OIS::MouseListener {

public:
	InputListener(Ogre::RenderWindow *wnd, Ogre::Camera *camera, Ogre::SceneManager *sceneMgr);
	~InputListener();
	
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
};