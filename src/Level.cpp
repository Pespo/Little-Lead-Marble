#include "Level.h"
#include "Application.h"

#include "InputListener.h"
#include "MotionState.h"
#include "Object.h"

llm::Level::Level( ) {

	llm::Application* app = llm::Application::getInstance();

	m_pPlayer = new Player();
	//m_pEnd = new End();

	//Initialisation de la scene
	srand(time(NULL));
	app->sceneManagerLevel()->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
	//app->app->sceneManagerLevel()()->setShadowTextureSize(2048);
	app->sceneManagerLevel()->setShadowColour(Ogre::ColourValue(0.6, 0.6, 0.6));
	//app->app->sceneManagerLevel()()->setShadowTextureCount(1);

	//Initialisation de la caméra
    app->camera()->setPosition(0,50,150);	
    app->camera()->lookAt(0,20,0);
	app->camera()->setNearClipDistance(5);
 
 	//Initialisation du viewport
	Ogre::Viewport* vp = app->window()->addViewport(app->camera());
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	app->camera()->setAspectRatio(Ogre::Real(vp->getActualWidth( )) / Ogre::Real(vp->getActualHeight( )));

	Ogre::Light* light0 = app->sceneManagerLevel()->createLight("light0");
    light0->setPosition(Ogre::Vector3(0,50,0));
    light0->setDiffuseColour(0.4,0.4,0.4);
    light0->setType(Ogre::Light::LT_SPOTLIGHT);
    light0->setDirection(0,-50,0);
    light0->setSpotlightRange (Ogre::Radian(0.f), Ogre::Radian(0.2f), 0.2);
 
    //mSceneMgr->setAmbientLight(Ogre::ColourValue(0.1, 0.1, 0.1));

	app->world()->setGravity(btVector3(0,-10,0));

	//Création du sol
	Object* ground = new Object("ground", "cube", app->world(), app->sceneManagerLevel(), Ogre::Vector3(200,1,200), 0);
	ground->entity()->setMaterialName("Cube");
	m_statics.push_back(ground);
 
 	//Création des pinguins
    for(int i=0; i<20; i++) {
		//std::cout << "i " << i << std::endl;
        Object* cube = new Object("penguin" + Ogre::StringConverter::toString(i), "penguin", app->world(), app->sceneManagerLevel(), Ogre::Vector3(10,10,10), 40);
        cube->rigidBody( )->translate(btVector3(rand( )%20-10, rand( )%100+50, rand( )%20-10));
       	m_statics.push_back(cube);
    }

}

llm::Level::~Level( ) {
	for(int i=0; i<m_statics.size( ); i++)
        delete m_statics[i];
    m_statics.clear( );
    for(int i=0; i<m_magnets.size( ); i++)
        delete m_magnets[i];
    m_magnets.clear( );
    for(int i=0; i<m_dangers.size( ); i++)
        delete m_dangers[i];
    m_dangers.clear( );
    for(int i=0; i<m_cubes.size( ); i++)
        delete m_cubes[i];
    m_cubes.clear( );

	delete m_pPlayer;
	//delete m_pEnd;

}

bool llm::Level::loop() {
	//Simuler l'application ( met à jours les corps )
	llm::Application* app = llm::Application::getInstance();
    app->world()->stepSimulation(1.f/60, 10);

	return true;
}