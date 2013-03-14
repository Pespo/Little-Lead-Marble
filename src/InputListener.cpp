#include "InputListener.h"

llm::InputListener::InputListener(Ogre::RenderWindow *window, Ogre::Camera *camera, Ogre::SceneManager *sceneManager) {
	m_pWindow = window;
	m_pCamera = camera;
	startOIS( );
	windowResized(m_pWindow);
	Ogre::WindowEventUtilities::addWindowEventListener(m_pWindow, this);

	m_pSceneManager = sceneManager;
    m_bContinue = true;
 
    m_mouvement = Ogre::Vector3::ZERO;
    m_vitesse = 100;
    m_vitesseRotation = 0.2;

	m_pMouse->setEventCallback(this);
	m_pKeyboard->setEventCallback(this);

}

llm::InputListener::~InputListener( ){
	Ogre::WindowEventUtilities::removeWindowEventListener(m_pWindow, this);
	windowClosed(m_pWindow);
}

bool llm::InputListener::frameRenderingQueued(const Ogre::FrameEvent& evt) {
//	std::cout << "Frame Rendering Queued" << std::endl;
	if(m_pWindow->isClosed( ))
		return false;

	if(m_pMouse)
        m_pMouse->capture( );
    if(m_pKeyboard)
        m_pKeyboard->capture( );
 
    Ogre::Vector3 deplacement = Ogre::Vector3::ZERO;
    deplacement = m_mouvement * m_vitesse * evt.timeSinceLastFrame;
    m_pCamera->moveRelative(deplacement);
 
    return m_bContinue;
}

void llm::InputListener::startOIS( ) {
	Ogre::LogManager::getSingletonPtr( )->logMessage("*** Initializing OIS ***");

	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
	  
	m_pWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str( )));

	m_pInputManager = OIS::InputManager::createInputSystem( pl );

	m_pMouse = static_cast<OIS::Mouse*>(m_pInputManager->createInputObject( OIS::OISMouse, true ));
	m_pKeyboard = static_cast<OIS::Keyboard*>(m_pInputManager->createInputObject( OIS::OISKeyboard, true ));
}

void llm::InputListener::windowResized(Ogre::RenderWindow* window) {
    unsigned int width, height, depth;
    int left, top;
    window->getMetrics(width, height, depth, left, top);
  
    const OIS::MouseState &ms = m_pMouse->getMouseState( );
    ms.width = width;
    ms.height = height;
}

void llm::InputListener::windowClosed(Ogre::RenderWindow* window) {
    if( window == m_pWindow ) {
        if( m_pInputManager ) {
            m_pInputManager->destroyInputObject( m_pMouse );
            m_pInputManager->destroyInputObject( m_pKeyboard );
  
            OIS::InputManager::destroyInputSystem(m_pInputManager);
            m_pInputManager = 0;
        }
    }
}


bool llm::InputListener::mouseMoved(const OIS::MouseEvent &e) {
	m_pCamera->yaw(Ogre::Degree(-m_vitesseRotation * e.state.X.rel));
    m_pCamera->pitch(Ogre::Degree(-m_vitesseRotation * e.state.Y.rel));
    return true;
}

bool llm::InputListener::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
    return true; 
}

bool llm::InputListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id){
    return true;
}
  
bool llm::InputListener::keyPressed(const OIS::KeyEvent &e){
	std::cout << "keyPressed" << std::endl;
	switch(e.key) {
		case OIS::KC_ESCAPE:
			m_bContinue = false;
			break;
		case OIS::KC_W:
			m_mouvement.z -= 1;
			break;
		case OIS::KC_S:
			m_mouvement.z += 1;
			break;
		case OIS::KC_A:
			m_mouvement.x -= 1;
			break;
		case OIS::KC_D:
			m_mouvement.x += 1;
			break;
		case OIS::KC_LSHIFT:
			m_vitesse *= 2;
			break;
	}
    return m_bContinue;
}

bool llm::InputListener::keyReleased(const OIS::KeyEvent &e){
	switch(e.key) {
		case OIS::KC_W:
			m_mouvement.z += 1;
			break;
		case OIS::KC_S:
			m_mouvement.z -= 1;
			break;
		case OIS::KC_A:
			m_mouvement.x += 1;
			break;
		case OIS::KC_D:
			m_mouvement.x -= 1;
			break;
		case OIS::KC_LSHIFT:
			m_vitesse /= 2;
			break;
    }
    return true;
}