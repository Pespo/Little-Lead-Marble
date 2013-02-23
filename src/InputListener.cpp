#include "InputListener.h"

InputListener::InputListener(Ogre::RenderWindow *wnd, Ogre::Camera *camera, Ogre::SceneManager *sceneMgr) {
	mWindow = wnd;
	mCamera = camera;
	startOIS();
	windowResized(mWindow);
	Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);

	mSceneMgr = sceneMgr;
    mContinuer = true;
 
    mMouvement = Ogre::Vector3::ZERO;
    mVitesse = 100;
    mVitesseRotation = 0.2;

	mMouse->setEventCallback(this);
	mKeyboard->setEventCallback(this);

}

InputListener::~InputListener(){
	Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
	windowClosed(mWindow);
}

bool InputListener::frameRenderingQueued(const Ogre::FrameEvent& evt) {
	std::cout << "Frame Rendering Queued" << std::endl;
	if(mWindow->isClosed())
		return false;

	if(mMouse)
        mMouse->capture();
    if(mKeyboard)
        mKeyboard->capture();
 
    Ogre::Vector3 deplacement = Ogre::Vector3::ZERO;
    deplacement = mMouvement * mVitesse * evt.timeSinceLastFrame;
    mCamera->moveRelative(deplacement);
 
    return mContinuer;
}

void InputListener::startOIS() {
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");

	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
	  
	mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	mInputManager = OIS::InputManager::createInputSystem( pl );

	mMouse = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse, true ));
	mKeyboard = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, true ));
}

void InputListener::windowResized(Ogre::RenderWindow* wnd) {
    unsigned int width, height, depth;
    int left, top;
    wnd->getMetrics(width, height, depth, left, top);
  
    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

void InputListener::windowClosed(Ogre::RenderWindow* wnd) {
    if( wnd == mWindow ) {
        if( mInputManager ) {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );
  
            OIS::InputManager::destroyInputSystem(mInputManager);
            mInputManager = 0;
        }
    }
}


bool InputListener::mouseMoved(const OIS::MouseEvent &e) {
	mCamera->yaw(Ogre::Degree(-mVitesseRotation * e.state.X.rel));
    mCamera->pitch(Ogre::Degree(-mVitesseRotation * e.state.Y.rel));
    return true;
}

bool InputListener::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
    return true; 
}

bool InputListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id){
    return true;
}
  
bool InputListener::keyPressed(const OIS::KeyEvent &e){
	std::cout << "keyPressed" << std::endl;
	switch(e.key) {
		case OIS::KC_ESCAPE:
			mContinuer = false;
			break;
		case OIS::KC_W:
			mMouvement.z -= 1;
			break;
		case OIS::KC_S:
			mMouvement.z += 1;
			break;
		case OIS::KC_A:
			mMouvement.x -= 1;
			break;
		case OIS::KC_D:
			mMouvement.x += 1;
			break;
		case OIS::KC_LSHIFT:
			mVitesse *= 2;
			break;
	}
    return mContinuer;
}

bool InputListener::keyReleased(const OIS::KeyEvent &e){
	switch(e.key) {
		case OIS::KC_W:
			mMouvement.z += 1;
			break;
		case OIS::KC_S:
			mMouvement.z -= 1;
			break;
		case OIS::KC_A:
			mMouvement.x += 1;
			break;
		case OIS::KC_D:
			mMouvement.x -= 1;
			break;
		case OIS::KC_LSHIFT:
			mVitesse /= 2;
			break;
    }
    return true;
}