#include "Application.h"
#include "InputListener.h"
#include "MotionState.h"
#include "Object.h"
#include "Level.h"
#include "Menu.h"
#include <math.h>

llm::Application::Application( ) : m_pRoot(0) {

	///-----initialization ogre-----
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
	m_pSceneManagerLevel = m_pRoot->createSceneManager("DefaultSceneManager", "Level Scene Manager");
	m_pSceneManagerMenu = m_pRoot->createSceneManager("DefaultSceneManager", "Menu Scene Manager");
	m_pCamera = m_pSceneManagerLevel->createCamera("PlayerCam");

	//initialisation frame listener
	m_pInputListener = new InputListener(m_pWindow, m_pCamera, m_pSceneManagerLevel);
    m_pRoot->addFrameListener(m_pInputListener);

	///-----initialization bullet phisics-----
	//collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	m_pCollisionConfiguration = new btDefaultCollisionConfiguration( );
	//use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
	//btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	m_pBroadphase = new btDbvtBroadphase( );
    //the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)    
    m_pSolver = new btSequentialImpulseConstraintSolver;
 	//initialize world with previous configuration
    m_pWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfiguration);

	//Chargement des ressources
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
	
    ///---------initialisation CEGUI -----------
    mRenderer = & CEGUI::OgreRenderer::bootstrapSystem();
}

llm::Application::~Application( ) {

	CEGUI::OgreRenderer::destroySystem();
	delete m_pLevel;
	delete m_pWorld;
	delete m_pSolver;
	delete m_pBroadphase;
	delete m_pDispatcher;
	delete m_pCollisionConfiguration;
    delete m_pInputListener;
	
	delete m_pRoot;
}

bool llm::Application::quit(const CEGUI::EventArgs &e) {
	//((InputListener*)m_pInputListener)->quit();
	return true;
}

bool llm::Application::start( ) {	
	m_pLevel = new Level();
	//llm::Menu* menu = new Menu();
	
	while(true)	{
		Ogre::WindowEventUtilities::messagePump( );

		//id = menu->loop();

		// if(id  valid)
			//level = loader::loader(id);

			//level->loop();
		m_pLevel->loop();

		if(m_pWindow->isClosed( ))
			return false; 
  
		if(!m_pRoot->renderOneFrame( ))
			return false;
	}

 	return true;
}