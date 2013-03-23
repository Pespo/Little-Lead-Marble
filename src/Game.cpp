#include "Game.h"
#include "Application.h"
#include "DotSceneLoader.h"
#include "Magnet.h"


inline btVector3 cvt(const Ogre::Vector3 &V){
    return btVector3(V.x, V.y, V.z);
}

llm::Game::Game() : m_indiceCubeSelected(-1) {

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
    m_pWorld = new btSimpleDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfiguration);
    m_pWorld->setGravity(btVector3(0,-10,0));

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
 	m_pLevel = new Level();
    m_pLevel->load();
	// --  /!\ Only decomment this if your folder with level_2 XML and ressources is ready
	//loadPlayer(); //load Player for the level's starting 
}

void llm::Game::loadPlayer() {
	//to do  @ add parameters for dynamic construction
	Magnet* bille = new Magnet("player", "bille", MARBLE, Ogre::Vector3(10., 10., 10.), 10, false, 50);
	m_pPlayer->magnet(bille);
	m_pPlayer->magnet()->body()->translate(cvt(m_pPlayer->getStartingPosition()));
	//m_pCamera->setPosition(Ogre::Vector3(m_pPlayer->getStartingPosition().x, m_pPlayer->getStartingPosition().y, 10.));

}

void llm::Game::loop() {
    if( m_indiceCubeSelected != -1 ) {
    	CEGUI::Point mouseCursor = CEGUI::MouseCursor::getSingleton().getPosition();
		cubeNextPosition( mouseCursor.d_x, mouseCursor.d_y );
    }

	m_pWorld->stepSimulation(1.f/60, 10);
}

bool llm::Game::cubeHit( int x, int y ) {
	llm::Application* app = llm::Application::getInstance();
	Ogre::Real xNormalized = static_cast<Ogre::Real>(x) / static_cast<Ogre::Real>( app->window()->getWidth() );
	Ogre::Real yNormalized = static_cast<Ogre::Real>(y) / static_cast<Ogre::Real>( app->window()->getHeight() );
	Ogre::Ray ray = m_pCamera->getCameraToViewportRay( xNormalized, yNormalized );

	if( m_indiceCubeSelected == -1 ) { // No cube selected
		for( int i = 0 ; i < m_pLevel->cubes().size() ; ++i ) {
			if( ray.intersects( m_pLevel->cubes()[i]->node()->_getWorldAABB() ).first) { 
				m_indiceCubeSelected = i;
				m_pLevel->cubes()[i]->selectCube();
				m_pLevel->cubes()[i]->body()->setAngularVelocity(btVector3(0,0,0));
				//world()->removeRigidBody( m_pLevel->cubes()[i]->rigidBody() );
				return true;
			}
		}
	}
	else {
		//world()->addRigidBody( m_pLevel->cubes()[m_indiceCubeSelected]->rigidBody() );
		m_pLevel->cubes()[m_indiceCubeSelected]->body()->setLinearVelocity(btVector3(0,0,0));

		m_pLevel->cubes()[m_indiceCubeSelected]->releaseCube();
		m_indiceCubeSelected = -1;
	}
	return false;
}

void llm::Game::cubeNextPosition( float x, float y ) {

	llm::Application* app = llm::Application::getInstance();
	Ogre::Real xNormalized = static_cast<Ogre::Real>(x) / static_cast<Ogre::Real>( app->window()->getWidth() );
	Ogre::Real yNormalized = static_cast<Ogre::Real>(y) / static_cast<Ogre::Real>( app->window()->getHeight() );
	Ogre::Ray ray = m_pCamera->getCameraToViewportRay( xNormalized, yNormalized );

	Ogre::Vector3 position = ray.getPoint( ray.intersects( m_pLevel->plane() ).second );
	m_pLevel->cubes()[m_indiceCubeSelected]->move(position);
}

