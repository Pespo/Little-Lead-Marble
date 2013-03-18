#include "InputListenerCEGUI.h"
#include <CEGUI.h>

llm::InputListenerCEGUI::InputListenerCEGUI(Ogre::RenderWindow *window, Ogre::Camera *camera, Ogre::SceneManager *sceneManager) :
    InputListener(window, camera, sceneManager) { }

bool llm::InputListenerCEGUI::mouseMoved(const OIS::MouseEvent &e) {
    CEGUI::System::getSingleton().injectMouseMove(e.state.X.rel, e.state.Y.rel);
    return true;
}

CEGUI::MouseButton llm::InputListenerCEGUI::convertButton(OIS::MouseButtonID buttonID) {
    std::cout << "INJECT--------------" << std ::endl;
    switch (buttonID) {
    case OIS::KC_ESCAPE:
            m_bContinue = false;
            break;
    // case OIS::MB_Left:
    //     return CEGUI::LeftButton;
  
    // case OIS::MB_Right:
    //     return CEGUI::RightButton;	
  
    // case OIS::MB_Middle:
    //     return CEGUI::MiddleButton;
  
    default:
        return CEGUI::LeftButton;
    }
}

bool llm::InputListenerCEGUI::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id) {
	CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
    return true; 
}

bool llm::InputListenerCEGUI::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id){
	CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
    return true;
}
  
bool llm::InputListenerCEGUI::keyPressed(const OIS::KeyEvent &e){
	std::cout << "keyPressed" << std::endl;
	CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectKeyDown(e.key);
    sys.injectChar(e.text);
    return true;
}

bool llm::InputListenerCEGUI::keyReleased(const OIS::KeyEvent &e){
	CEGUI::System::getSingleton().injectKeyUp(e.key);
    return true;
}

void llm::InputListenerCEGUI::quit( ) {
	m_bContinue = false;
}