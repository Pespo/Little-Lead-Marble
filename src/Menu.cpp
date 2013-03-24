#include "Menu.h"
#include "Application.h"

#include <CEGUI.h>

llm::Menu::Menu() {
	m_pSceneManager = llm::Application::getInstance()->root()->createSceneManager( "DefaultSceneManager", "Menu" );
	m_pCamera = m_pSceneManager->createCamera( "Camera" );
	m_pCamera->setNearClipDistance(5);

	 ///---------initialisation CEGUI -----------
    CEGUI::OgreRenderer::bootstrapSystem();

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
 
	rgm.initialiseAllResourceGroups();
	
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
    CEGUI::ImagesetManager::getSingleton().createFromImageFile("BackgroundImage","MenuBackground.tga");

	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	llm::Application* app = llm::Application::getInstance();

	/******* Menu ********/
	CEGUI::Window *Menu = wmgr.createWindow("DefaultWindow", "Menu"); //conteneur
	CEGUI::System::getSingleton().setGUISheet(Menu);//Linkage du conteneur a CEGUI

	/******StartMenu*****/
	CEGUI::Window *startMenu = wmgr.createWindow("TaharezLook/StaticImage", "StartMenu/Sheet"); //conteneur
	startMenu->setPosition( CEGUI::UVector2( CEGUI::UDim( 0, 0 ), CEGUI::UDim( 0, 0 ) ) );
    startMenu->setSize(CEGUI::UVector2(CEGUI::UDim(1, 0), CEGUI::UDim(1, 0)));  
    startMenu->setProperty( "Image", "set:BackgroundImage image:full_image" );
    Menu->addChildWindow(startMenu);
	
	CEGUI::Window *options = wmgr.createWindow("TaharezLook/OptionsButton", "StartMenu/OptionsButton");
    //quit->setText("Options");
    options->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.2f, 0 ), CEGUI::UDim( 0.8f, 0 ) ) );
    options->setSize(CEGUI::UVector2(CEGUI::UDim(0.18, 0), CEGUI::UDim(0.16, 0)));
    startMenu->addChildWindow(options);//intégration du bouton dans le conteneur	

	CEGUI::Window *start = wmgr.createWindow("TaharezLook/PlayButton", "StartMenu/StartButton"); //bouton
	//start->setText("Start");
	start->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.4f, 0 ), CEGUI::UDim( 0.75f, 0 ) ) );
    start->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.19f, 0)));
    startMenu->addChildWindow(start);//intégration du bouton dans le conteneur

	CEGUI::Window *quitStart = wmgr.createWindow("TaharezLook/QuitButton", "StartMenu/QuitButton"); //bouton
    //quit->setText("Quit");
    quitStart->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.62f, 0 ), CEGUI::UDim( 0.8f, 0 ) ) );
    quitStart->setSize(CEGUI::UVector2(CEGUI::UDim(0.18, 0), CEGUI::UDim(0.16, 0)));
    startMenu->addChildWindow(quitStart);//intégration du bouton dans le conteneur

	wmgr.getWindow("StartMenu/StartButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&llm::Application::startGame, app));//event du bouton
	wmgr.getWindow("StartMenu/QuitButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&llm::Application::quit, app));//event du bouton

	/******PauseMenu*****/
	CEGUI::Window *PauseMenu = wmgr.createWindow("DefaultWindow", "PauseMenu/Sheet"); //conteneur
	Menu->addChildWindow(PauseMenu);

	CEGUI::Window *continued = wmgr.createWindow("TaharezLook/Button", "PauseMenu/ContinueButton"); //bouton
	continued->setText("Continue");
	continued->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.42f, 0 ), CEGUI::UDim( 0.40f, 0 ) ) );
	continued->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	PauseMenu->addChildWindow(continued);//intégration du bouton dans le conteneur

	CEGUI::Window *reset = wmgr.createWindow("TaharezLook/Button", "PauseMenu/ResetButton"); //bouton
	reset->setText("Reset");
	reset->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.42f, 0 ), CEGUI::UDim( 0.50f, 0 ) ) );
	reset->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	PauseMenu->addChildWindow(reset);//intégration du bouton dans le conteneur

	CEGUI::Window *quitPause = wmgr.createWindow("TaharezLook/Button", "PauseMenu/QuitButton"); //bouton
	quitPause->setText("Quit");
	quitPause->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.42f, 0 ), CEGUI::UDim( 0.60f, 0 ) ) );
	quitPause->setSize(CEGUI::UVector2(CEGUI::UDim(0.15, 0), CEGUI::UDim(0.05, 0)));
	PauseMenu->addChildWindow(quitPause);//intégration du bouton dans le conteneur
	
	wmgr.getWindow("PauseMenu/ContinueButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&llm::Application::pause, app));//event du bouton
	wmgr.getWindow("PauseMenu/ResetButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&llm::Application::reset, app));//event du bouton
	wmgr.getWindow("PauseMenu/QuitButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&llm::Application::quit, app));//event du bouton

	desactive();
}

llm::Menu::~Menu() { 
}

void llm::Menu::desactive() {
	startMenu( false );
	pauseMenu( false );
}

void llm::Menu::startMenu( bool visible ) {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	visible ? wmgr.getWindow("StartMenu/Sheet")->setVisible(true) : wmgr.getWindow("StartMenu/Sheet")->setVisible(false);
}

void llm::Menu::pauseMenu( bool visible ) {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	visible ? wmgr.getWindow("PauseMenu/Sheet")->setVisible(true) : wmgr.getWindow("PauseMenu/Sheet")->setVisible(false);
}