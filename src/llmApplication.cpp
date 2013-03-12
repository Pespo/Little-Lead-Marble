#include "llmApplication.h"
#include "llmInputListener.h"
#include "llmMotionState.h"
#include "llmObject.h"
#include <math.h>

llmApplication::llmApplication() : m_Root(0) {

	///-----initialization ogre-----
	//Définition du root(fichier de plugins à charger, fichier de configuration d'Ogre, fichier de log).
	m_Root = new Ogre::Root("../res/plugins.cfg", "../res/resources.cfg", "../res/Ogre.log");
	//Choose the render system (openGL for our case)
	Ogre::RenderSystem *rs = m_Root->getRenderSystemByName("OpenGL Rendering Subsystem");
	m_Root->setRenderSystem(rs);
	//Set options
	rs->setConfigOption("Full Screen", "No");
	rs->setConfigOption("Video Mode", "1280 x 800 @ 32-bit colour");
	rs->setConfigOption("VSync", "Yes");
	m_Window = m_Root->initialise(true, "Little Lead Marble");	

	m_SceneMgr = m_Root->createSceneManager("DefaultSceneManager", "Default Scene Manager");
	m_Camera = m_SceneMgr->createCamera("PlayerCam");
	createFrameListener();

	///-----initialization bullet phisics-----
	//collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	m_collisionConfiguration = new btDefaultCollisionConfiguration();
	//use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	//btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	m_broadphase = new btDbvtBroadphase();
    //the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)    
    m_solver = new btSequentialImpulseConstraintSolver;
 	//initialize world with previous configuration
    m_world = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
}

llmApplication::~llmApplication() {
}

void llmApplication::createFrameListener() {
    m_InputListener = new llmInputListener(m_Window, m_Camera, m_SceneMgr);
    m_Root->addFrameListener(m_InputListener);
}

void llmApplication::exit(){
	for(int i=0; i<m_objectList.size(); i++)
        delete m_objectList[i];
     m_objectList.clear();
	
	delete m_world;
	delete m_solver;
	delete m_broadphase;
	delete m_dispatcher;
	delete m_collisionConfiguration;
    delete m_InputListener;
	delete m_Root;
}

bool llmApplication::start() {	
	//Chargement des ressources
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

	srand(time(NULL));

	m_SceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	//m_SceneMgr->setShadowTextureSize(2048);
	m_SceneMgr->setShadowColour(Ogre::ColourValue(0.6, 0.6, 0.6));
	//m_SceneMgr->setShadowTextureCount(1);

	Ogre::Light* light0 = m_SceneMgr->createLight("light0");
    light0->setPosition(Ogre::Vector3(0,50,0));
    light0->setDiffuseColour(0.4,0.4,0.4);
    light0->setType(Ogre::Light::LT_SPOTLIGHT);
    light0->setDirection(0,-50,0);
    light0->setSpotlightRange (Ogre::Radian(0.f), Ogre::Radian(0.2f), 0.2);
 
    //mSceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));

	m_world->setGravity(btVector3(0,-10,0));

	//Création du sol
	llmObject* ground = new llmObject("ground", "cube", m_world, m_SceneMgr, Ogre::Vector3(200,1,200), 0);
	ground->getEntity()->setMaterialName("Cube");
	m_objectList.push_back(ground);
 
 	//Création des pinguins
    for(int i=0; i<20; i++) {
		//std::cout << "i " << i << std::endl;
        llmObject* cube = new llmObject("penguin" + Ogre::StringConverter::toString(i), "penguin", m_world, m_SceneMgr, Ogre::Vector3(10,10,10), 40);
        cube->getRigidBody()->translate(btVector3(rand()%20-10, rand()%100+50, rand()%20-10));
       	m_objectList.push_back(cube);
    }
 
 	//Initialisation de la caméra
    m_Camera->setPosition(0,50,150);	
    m_Camera->lookAt(0,20,0);
	m_Camera->setNearClipDistance(5);
 
 	//Initialisation du viewport
	Ogre::Viewport* vp = m_Window->addViewport(m_Camera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	m_Camera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	int i = 0;
	while(true)	{
		i++;
		Ogre::WindowEventUtilities::messagePump();
       
	   if(i>180){
	   	m_objectList[1]->getRigidBody()->applyCentralImpulse(btVector3(0., 50., 0.));
	   }
	   if(i>190)
			i=0;

		//Simuler l'application ( met à jours les corps )
        m_world->stepSimulation(1.f/60, 10);
        

		if(m_Window->isClosed())
			return false; 
  
		if(!m_Root->renderOneFrame())
			return false;
	}

 	return true;
}