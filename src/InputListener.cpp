#include "Application.h"
#include "InputListener.h"
#include <CEGUI.h>
#include <string>

llm::InputListener::InputListener(Ogre::RenderWindow *window) {
	startOIS(window);
	windowResized(window);
	Ogre::WindowEventUtilities::addWindowEventListener(window, this);

    m_bContinue = true;
 
    m_mouvement = Ogre::Vector3::ZERO;
    m_vitesse = 100;
    m_vitesseRotation = 0.2;

	m_pMouse->setEventCallback(this);
	m_pKeyboard->setEventCallback(this);
}

llm::InputListener::~InputListener( ){
	Ogre::WindowEventUtilities::removeWindowEventListener(llm::Application::getInstance()->window(), this);
	windowClosed();
}

bool llm::InputListener::frameRenderingQueued(const Ogre::FrameEvent& evt) {
//	std::cout << "Frame Rendering Queued" << std::endl;
	if(llm::Application::getInstance()->window()->isClosed( ))
		return false;

	if(m_pMouse)
        m_pMouse->capture( );
    if(m_pKeyboard)
        m_pKeyboard->capture( );
 
    Ogre::Vector3 deplacement = Ogre::Vector3::ZERO;
    deplacement = m_mouvement * m_vitesse * evt.timeSinceLastFrame;
    llm::Application::getInstance()->game()->camera()->moveRelative(deplacement);
 
    return m_bContinue;
}

void llm::InputListener::startOIS( Ogre::RenderWindow *window ) {
	Ogre::LogManager::getSingletonPtr( )->logMessage("*** Initializing OIS ***");

	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;
	  
	window->getCustomAttribute("WINDOW", &windowHnd);
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

void llm::InputListener::windowClosed() {
    if( m_pInputManager ) {
        m_pInputManager->destroyInputObject( m_pMouse );
        m_pInputManager->destroyInputObject( m_pKeyboard );
  
        OIS::InputManager::destroyInputSystem(m_pInputManager);
        m_pInputManager = 0;
    }
}


bool llm::InputListener::mouseMoved(const OIS::MouseEvent &e) {
	//m_pCamera->yaw(Ogre::Degree(-m_vitesseRotation * e.state.X.rel));
    //m_pCamera->pitch(Ogre::Degree(-m_vitesseRotation * e.state.Y.rel));
    CEGUI::System::getSingleton().injectMouseMove(e.state.X.rel, e.state.Y.rel);
    llm::Application* app = llm::Application::getInstance();
    if( app->game()->cubeSelected() != -1 ) {
		app->game()->cubeNextPosition( e.state.X.abs, e.state.Y.abs );
    }
    return true;
}

bool llm::InputListener::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) {

	if(llm::Application::getInstance()->inGame()){
		if( id == OIS::MB_Left ) {
			llm::Application* app = llm::Application::getInstance();
			int selectedCube = app->game()->cubeSelected();
			std::cout << "Clic, selectedCube: " << selectedCube << std::endl;
			app->game()->cubeHit( e.state.X.abs, e.state.Y.abs );
		} 
	} else {
		CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
	}
    return true; 
}

bool llm::InputListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id){
	if(llm::Application::getInstance()->inGame()){

	} else {
		CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
	}
    return true;
}
  
bool llm::InputListener::keyPressed(const OIS::KeyEvent &e){
	std::cout << "keyPressed" << std::endl;
	if(llm::Application::getInstance()->inGame()) {
		switch(e.key) {
			case OIS::KC_ESCAPE:
				llm::Application::getInstance()->pause();
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
	} else {
		CEGUI::System &sys = CEGUI::System::getSingleton();
	    sys.injectKeyDown(convertKey(e));
	   // sys.injectChar(e.text);
	}
    return m_bContinue;
}

bool llm::InputListener::keyReleased(const OIS::KeyEvent &e) {
	if(llm::Application::getInstance()->inGame()) {
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
	} else {
    	CEGUI::System::getSingleton().injectKeyUp(e.key);
    }
    return true;
}

void llm::InputListener::quit( ) {
	m_bContinue = false;
}

CEGUI::MouseButton llm::InputListener::convertButton(OIS::MouseButtonID buttonID) {
    switch (buttonID) {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
  
    case OIS::MB_Right:
        return CEGUI::RightButton;	
  
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
  
    default:
        return CEGUI::LeftButton;
    }
}

CEGUI::Key::Scan llm::InputListener::convertKey(OIS::KeyEvent e) {
    switch(e.key) {
	case OIS::KC_ESCAPE:
		quit();
		return CEGUI::Key::Scan::Escape;
	}
}