#include "Game.h"
#include "Application.h"

llm::Game::Game() {

	//Init game scene manager 
	m_pSceneManager = llm::Application::getInstance()->root()->createSceneManager("DefaultSceneManager", "Level Scene Manager");
	m_pSceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	m_pSceneManager->setShadowColour(Ogre::ColourValue(0.2, 0.2, 0.2));
	m_pSceneManager->setAmbientLight(Ogre::ColourValue(0.6, 0.6, 0.6));

	//Init camera
	m_pCamera = m_pSceneManager->createCamera("Camera");
	m_pCamera->setPosition(0,50,200);	
    m_pCamera->lookAt(0,20,0);
	m_pCamera->setNearClipDistance(5);

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
    m_pWorld->setGravity(btVector3(0,-10,0));

    m_pLevel = new Level();
    m_pPlayer = new Player();
}

llm::Game::~Game() {
	delete m_pPlayer;
	delete m_pLevel;
	delete m_pWorld;
	delete m_pSolver;
	delete m_pBroadphase;
	delete m_pDispatcher;
	delete m_pCollisionConfiguration;
}

void llm::Game::loadLevel() {

	Ogre::Light* light0 = m_pSceneManager->createLight("light0");
    light0->setPosition(Ogre::Vector3(0,200,0));
    light0->setDiffuseColour(0.8,0.8,0.8);
    light0->setType(Ogre::Light::LT_SPOTLIGHT);
    light0->setDirection(0,-1,0);
    light0->setSpotlightRange (Ogre::Radian(3.14/8.), Ogre::Radian(3.14/8.), 5);

    m_pLevel->load();
}

void llm::Game::loop() {
	m_pWorld->stepSimulation(1.f/60, 10);
}

