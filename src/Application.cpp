#include "Application.h"
#include "InputListener.h"
#include "MotionState.h"
#include "Object.h"
#include <math.h>

llm::Application::Application( ) : m_pRoot(0) {

	///-----initialization ogre-----
	//Définition du root(fichier de plugins à charger, fichier de configuration d'Ogre, fichier de log).
	m_pRoot = new Ogre::Root("../res/plugins.cfg", "../res/resources.cfg", "../res/Ogre.log");
	//Choose the render system (openGL for our case)
	Ogre::RenderSystem *rs = m_pRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
	m_pRoot->setRenderSystem(rs);
	//Set options
	rs->setConfigOption("Full Screen", "No");
	rs->setConfigOption("Video Mode", "1280 x 800 @ 32-bit colour");
	rs->setConfigOption("VSync", "Yes");
	m_pWindow = m_pRoot->initialise(true, "Little Lead Marble");	

	m_pSceneMgr = m_pRoot->createSceneManager("DefaultSceneManager", "Default Scene Manager");
	m_pCamera = m_pSceneMgr->createCamera("PlayerCam");
	createFrameListener( );

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
}

llm::Application::~Application( ) { }

void llm::Application::createFrameListener( ) {
    m_pInputListener = new InputListener(m_pWindow, m_pCamera, m_pSceneMgr);
    m_pRoot->addFrameListener(m_pInputListener);
}

void llm::Application::exit( ) {
	for(int i=0; i<m_objectList.size( ); i++)
        delete m_objectList[i];
     m_objectList.clear( );
	
	delete m_pWorld;
	delete m_pSolver;
	delete m_pBroadphase;
	delete m_pDispatcher;
	delete m_pCollisionConfiguration;
    delete m_pInputListener;
	delete m_pRoot;
}

bool llm::Application::start( ) {	
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

	srand(time(NULL));

	m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	//m_pSceneMgr->setShadowTextureSize(2048);
	m_pSceneMgr->setShadowColour(Ogre::ColourValue(0.6, 0.6, 0.6));
	//m_pSceneMgr->setShadowTextureCount(1);

	Ogre::Light* light0 = m_pSceneMgr->createLight("light0");
    light0->setPosition(Ogre::Vector3(0,50,0));
    light0->setDiffuseColour(0.4,0.4,0.4);
    light0->setType(Ogre::Light::LT_SPOTLIGHT);
    light0->setDirection(0,-50,0);
    light0->setSpotlightRange (Ogre::Radian(0.f), Ogre::Radian(0.2f), 0.2);
 
    //mSceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));

	m_pWorld->setGravity(btVector3(0,-10,0));

	//Création du sol
	Object* ground = new Object("ground", "cube", m_pWorld, m_pSceneMgr, Ogre::Vector3(200,1,200), 0);
	ground->getEntity( )->setMaterialName("Cube");
	m_objectList.push_back(ground);
 
 	//Création des pinguins
    for(int i=0; i<20; i++) {
		//std::cout << "i " << i << std::endl;
        Object* cube = new Object("penguin" + Ogre::StringConverter::toString(i), "penguin", m_pWorld, m_pSceneMgr, Ogre::Vector3(10,10,10), 40);
        cube->getRigidBody( )->translate(btVector3(rand( )%20-10, rand( )%100+50, rand( )%20-10));
       	m_objectList.push_back(cube);
    }
 
 	//Initialisation de la caméra
    m_pCamera->setPosition(0,50,150);	
    m_pCamera->lookAt(0,20,0);
	m_pCamera->setNearClipDistance(5);
 
 	//Initialisation du viewport
	Ogre::Viewport* vp = m_pWindow->addViewport(m_pCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	m_pCamera->setAspectRatio(Ogre::Real(vp->getActualWidth( )) / Ogre::Real(vp->getActualHeight( )));

	int i = 0;
	while(true)	{
		i++;
		Ogre::WindowEventUtilities::messagePump( );
       
	   if(i>180){
	   	m_objectList[1]->getRigidBody( )->applyCentralImpulse(btVector3(0., 50., 0.));
	   }
	   if(i>190)
			i=0;

		//Simuler l'application ( met à jours les corps )
        m_pWorld->stepSimulation(1.f/60, 10);
        

		if(m_pWindow->isClosed( ))
			return false; 
  
		if(!m_pRoot->renderOneFrame( ))
			return false;
	}

 	return true;
}