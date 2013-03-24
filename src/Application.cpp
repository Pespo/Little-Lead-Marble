#include "Application.h"
#include "InputListener.h"

llm::Application::Application() : m_pRoot(0) {

	//Définition du root(fichier de plugins à charger, fichier de configuration d'Ogre, fichier de log).
	m_pRoot = new Ogre::Root("../res/plugins.cfg", "../res/resources.cfg", "/Ogre.log");

	//Choose the render system (openGL for our case)
	Ogre::RenderSystem *rs = m_pRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
	m_pRoot->setRenderSystem(rs);

	//Set options
	rs->setConfigOption("Full Screen", "No");
	rs->setConfigOption("Video Mode", "800 x 600 @ 32-bit colour");
	rs->setConfigOption("VSync", "Yes");
	m_pWindow = m_pRoot->initialise(true, "Little Lead Marble");	

    loadRessource();

    m_bInGame = false;
}

llm::Application::~Application() {
	CEGUI::OgreRenderer::destroySystem();
	delete m_pInputListener;
	delete m_pGame;
	delete m_pMenu;
	delete m_pRoot;
}

bool llm::Application::start() {	

	m_pGame = new Game();
	m_pMenu = new Menu();
	m_pMenu->startMenu(true);

	m_pInputListener = new InputListener( m_pWindow );
    m_pRoot->addFrameListener(m_pInputListener);

	setupViewport(MENU);

	while(true)	{
		Ogre::WindowEventUtilities::messagePump();
		if(m_bInGame)
			m_pGame->loop();

		if(m_pWindow->isClosed())
			return false; 

		if(!m_pRoot->renderOneFrame())
			return false;
	}

 	return true;
}

void llm::Application::loadRessource() {
	Ogre::ConfigFile configFile;
	configFile.load("../res/resources.cfg"); //Permet de charger les ressources
	Ogre::ConfigFile::SectionIterator seci = configFile.getSectionIterator(); //iterteur qui va permettre de parcourir le fichier ressource.cfg
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements()) {
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i) {
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void llm::Application::setupViewport(viewport v) {
	Ogre::Camera *cam;
	Ogre::Viewport *vp;
	m_pWindow->removeAllViewports();
 	if(v == GAME) {
		cam = m_pGame->camera(); //The Camera
		vp = m_pWindow->addViewport(cam); //Our Viewport linked to the camera
	} else { 
		cam = m_pMenu->camera(); //The Camera
		vp = m_pWindow->addViewport(cam); //Our Viewport linked to the camera
	}
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	cam->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

bool llm::Application::quit() {
	((InputListener*)m_pInputListener)->quit();
	return true;
}
bool llm::Application::quit(const CEGUI::EventArgs &e) { quit(); return true; }

void llm::Application::startGame() {
	m_pGame->loadLevel();
	m_bInGame = true;
	setupViewport(GAME);
	m_pMenu->startMenu(false);
}
bool llm::Application::startGame(const CEGUI::EventArgs &e) { startGame(); return true; }

void llm::Application::pause() {
	if( !m_bInGame ) {
		m_bInGame = true;
		setupViewport(GAME);
		m_pMenu->desactive();
	} else {
		m_bInGame = false;
		setupViewport(MENU);
		m_pMenu->pauseMenu(true);
	}
}
bool llm::Application::pause(const CEGUI::EventArgs &e) { pause(); return true; }

void llm::Application::reset() {
	m_pGame->restart();
	pause();
}
bool llm::Application::reset(const CEGUI::EventArgs &e) { reset(); return true; }