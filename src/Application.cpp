#include "Application.h"
#include "InputListener.h"

llm::Application::Application( ) : m_pRoot(0) {

	//Définition du root(fichier de plugins à charger, fichier de configuration d'Ogre, fichier de log).
	m_pRoot = new Ogre::Root("../res/plugins.cfg", "../res/resources.cfg", "/Ogre.log");

	//Choose the render system (openGL for our case)
	Ogre::RenderSystem *rs = m_pRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
	m_pRoot->setRenderSystem(rs);

	//Set options
	rs->setConfigOption("Full Screen", "No");
	rs->setConfigOption("Video Mode", "1280 x 800 @ 32-bit colour");
	rs->setConfigOption("VSync", "Yes");
	m_pWindow = m_pRoot->initialise(true, "Little Lead Marble");	
	
	//initialisation frame listener
	m_pInputListener = new InputListener( m_pWindow );
    m_pRoot->addFrameListener(m_pInputListener);

    loadRessource();

    m_bInGame = false;
}

llm::Application::~Application( ) {
	CEGUI::OgreRenderer::destroySystem();
	delete m_pInputListener;
	delete m_pGame;
	delete m_pMenu;
	delete m_pRoot;
}

bool llm::Application::quit(const CEGUI::EventArgs &e) {
	std::cout << "Quit" << std::endl;
	((InputListener*)m_pInputListener)->quit();
	return true;
}

bool llm::Application::quit() {
	((InputListener*)m_pInputListener)->quit();
	return true;
}

bool llm::Application::start( ) {	
	m_pGame = new Game();
	m_pMenu = new Menu();

	setupViewport(m_pGame->sceneManager(), Ogre::String("Camera"));
	m_pGame->loadLevel();

	while(true)	{
		Ogre::WindowEventUtilities::messagePump( );

		if(m_bInGame)
			m_pGame->loop();

		if(m_pWindow->isClosed( ))
			return false; 

		if(!m_pRoot->renderOneFrame( ))
			return false;
	}

 	return true;
}

void llm::Application::setupViewport(Ogre::SceneManager* current, Ogre::String& cameraName) {
	m_pWindow->removeAllViewports();
 
	Ogre::Camera *cam = current->getCamera(cameraName); //The Camera
	Ogre::Viewport *vp = m_pWindow->addViewport(cam); //Our Viewport linked to the camera
	 
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

bool llm::Application::pause(const CEGUI::EventArgs &e) {
	m_bInGame = m_bInGame ? false : true;
	m_pMenu->startMenu(!m_bInGame);
	return true;
}

void llm::Application::pause() {
	m_bInGame = m_bInGame ? false : true;
	m_pMenu->startMenu(!m_bInGame);
}

void llm::Application::loadRessource() {
	Ogre::ConfigFile configFile;
	configFile.load("../res/resources.cfg"); //Permet de charger les ressources
	Ogre::ConfigFile::SectionIterator seci = configFile.getSectionIterator( ); //iterteur qui va permettre de parcourir le fichier ressource.cfg
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements( )) {
		secName = seci.peekNextKey( );
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext( );
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin( ); i != settings->end( ); ++i) {
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton( ).addResourceLocation(archName, typeName, secName);
		}
	}

	Ogre::TextureManager::getSingleton( ).setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton( ).initialiseAllResourceGroups( );
}