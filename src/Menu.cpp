#include "Menu.h"
#include "Application.h"

#include <CEGUI.h>

llm::Menu::Menu() {

	llm::Application* app = llm::Application::getInstance();
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
 
	rgm.initialiseAllResourceGroups( );
	
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

	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	/******StartMenu*****/
    CEGUI::Window *startMenu = wmgr.createWindow("TaharezLook/StaticImage", "StartMenu/Sheet"); //conteneur
	CEGUI::System::getSingleton().setGUISheet(startMenu);//Linkage du conteneur a CEGUI


    CEGUI::ImagesetManager::getSingleton().createFromImageFile("BackgroundImage","MenuBackground.tga");
	//CEGUI::Window *startMenu = wmgr.createWindow("Taharez/StaticImage", "StartMenu/Background"); //conteneur
	//CEGUI::System::getSingleton().setGUISheet(startMenu);//Linkage du conteneur a CEGUI
    startMenu->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0f, 0.0f), CEGUI::UDim( 0.0f, 0.0f ) ) );
	startMenu->setSize( CEGUI::UVector2( CEGUI::UDim( 1.0f, 0.0f), CEGUI::UDim( 1.0f, 0.0f ) ) );
	startMenu->setProperty( "Image", "set:BackgroundImage image:full_image" );

    // BACKGROUND IMAGE
    /*CEGUI::ImagesetManager::getSingleton().createFromImageFile("BackgroundImage","MenuBackground.tga");
    CEGUI::Window *background = wmgr.createWindow("TaharezLook/StaticImage", "StartMenu/MenuBackground");
    background->setPosition( CEGUI::UVector2( CEGUI::UDim( 0, 0 ), CEGUI::UDim( 0, 0 ) ) );
    background->setSize(CEGUI::UVector2(CEGUI::UDim(1, 0), CEGUI::UDim(1, 0)));
    startMenu->addChildWindow( background );*/
	

	// OPTIONS BUTTON
	CEGUI::Window *options = wmgr.createWindow("TaharezLook/OptionsButton", "StartMenu/OptionsButton"); 
	//quit->setText("Options");
	options->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.2f, 0 ), CEGUI::UDim( 0.8f, 0 ) ) );
	options->setSize(CEGUI::UVector2(CEGUI::UDim(0.18, 0), CEGUI::UDim(0.16, 0)));
	startMenu->addChildWindow(options);//intégration du bouton dans le conteneur

	// QUIT BUTTON
	CEGUI::Window *quit = wmgr.createWindow("TaharezLook/QuitButton", "StartMenu/QuitButton"); 
	//quit->setText("Quit");
	quit->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.62f, 0 ), CEGUI::UDim( 0.8f, 0 ) ) );
	quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.18, 0), CEGUI::UDim(0.16, 0)));
	startMenu->addChildWindow(quit);//intégration du bouton dans le conteneur

	// START BUTTON
	CEGUI::Window *start = wmgr.createWindow("TaharezLook/PlayButton", "StartMenu/StartButton"); //bouton
	//start->setText("Start");
	start->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.4f, 0 ), CEGUI::UDim( 0.75f, 0 ) ) );
	start->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.19f, 0)));
	startMenu->addChildWindow(start);//intégration du bouton dans le conteneur
	
	wmgr.getWindow("StartMenu/QuitButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&llm::Application::quit, app));//event du bouton
	//wmgr.getWindow("StartMenu/OptionsButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&llm::Application::options, app));//event du bouton
	wmgr.getWindow("StartMenu/StartButton")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&llm::Application::pause, app));//event du bouton
}

llm::Menu::~Menu() { }

void llm::Menu::startMenu(bool visible) {
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	visible ? wmgr.getWindow("StartMenu/Sheet")->setVisible(true) : wmgr.getWindow("StartMenu/Sheet")->setVisible(false);
}