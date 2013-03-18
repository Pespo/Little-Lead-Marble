#include "Menu.h"
#include "Application.h"
#include <Ogre.h>
#include <CEGUI.h>

llm::Menu::Menu() {

	llm::Application* app = llm::Application::getInstance();
	m_pSceneManager = app->root()->createSceneManager("DefaultSceneManager", "Menu Scene Manager");
	m_pCamera = m_pSceneManager->createCamera("PlayerCam");

    m_pInputListener = new InputListenerCEGUI(app->window(), m_pCamera, m_pSceneManager);
    app->root()->addFrameListener(m_pInputListener);

	/*****CEGUI*****/
    //Chargement des ressources
	Ogre::ResourceGroupManager& rgm = Ogre::ResourceGroupManager::getSingleton();

	rgm.createResourceGroup("imagesets");
	rgm.createResourceGroup("fonts");
	rgm.createResourceGroup("layouts");
	rgm.createResourceGroup("schemes");
	rgm.createResourceGroup("looknfeels");

	rgm.addResourceLocation( "../res/CEGUI/schemes/", "FileSystem", "Schemes");
	rgm.addResourceLocation( "../res/CEGUI/imagesets/", "FileSystem", "Imagesets");
	rgm.addResourceLocation( "../res/CEGUI/fonts/", "FileSystem", "Fonts");
	rgm.addResourceLocation( "../res/CEGUI/layouts/", "FileSystem", "Layouts");
	rgm.addResourceLocation( "../res/CEGUI/looknfeel/", "FileSystem", "LookNFeel");
 
	Ogre::ResourceGroupManager::getSingleton( ).initialiseAllResourceGroups( );
 	//Linkage des ressources avec CEGUI
    CEGUI::Imageset::setDefaultResourceGroup("Imagesets");
	CEGUI::Font::setDefaultResourceGroup("Fonts");
	CEGUI::Scheme::setDefaultResourceGroup("Schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
	CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

	//Définition
	CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
	CEGUI::System::getSingleton().setDefaultMouseCursor("TaharezLook", "MouseArrow");
	CEGUI::MouseCursor::getSingleton().setImage( CEGUI::System::getSingleton().getDefaultMouseCursor());

	//Affichage
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	CEGUI::Window *sheet = wmgr.createWindow("DefaultWindow", "CEGUIDemo/Sheet"); //conteneur

	CEGUI::Window *quit = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/QuitButton"); //bouton
	quit->setText("Quit");
	quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	sheet->addChildWindow(quit);//intégration du bouton dans le conteneur

	CEGUI::Window *start = wmgr.createWindow("TaharezLook/Button", "CEGUIDemo/StartButton"); //bouton
	start->setText("Start");
	start->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.25f, 0 ), CEGUI::UDim( 0.25f, 0 ) ) );
	start->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	sheet->addChildWindow(start);//intégration du bouton dans le conteneur

	CEGUI::System::getSingleton().setGUISheet(sheet);//Linkage du conteneur a CEGUI

	quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&llm::Application::quit, app));//event du bouton
	start->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&llm::Application::quit, app));//event du bouton
}

llm::Menu::~Menu() { }

void llm::Menu::loop() {

}