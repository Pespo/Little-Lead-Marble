#include "Level.h"
#include "Application.h"
#include "DotSceneLoader.h"
#include "InputListener.h"
#include "MotionState.h"
#include "Object.h"

#include <CEGUI.h>
#include <OgreRay.h>

llm::Level::Level( ) : m_startPosition( Ogre::Vector3( 0, 0, 0 ) ), m_plane( Ogre::Vector3( 0, 0, 1 ), Ogre::Vector3( 0, 0, 0 ) ),
						m_indiceCubeSelected(-1), m_bIsMagnetized( false ), m_bIsEnded( false ), m_bIsWon( false ) {

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

bool llm::Level::load() {
	//Import Scene
	
	//FUNCTION LOADING A SCENE FROM XML FILE
	/*llm::Application* app = llm::Application::getInstance();
	DotSceneLoader loader; */
   // loader.parseDotScene("scene1_test2.xml",Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME , app->sceneManagerLevel());

	//Verif remplissage lvl
	/*std::vector<Asset*> assetLvl = app->level()->statics();
	std::cout<<"Vector statics size ::: "<<assetLvl.size()<<std::endl;
	for(int j=0; j<assetLvl.size(); ++j){
		std::cout<<"NODE NAME :"<<assetLvl[j]->getAssetName()<<std::endl;
		std::cout<<"ENTITY NAME :"<<assetLvl[j]->entity()->getName()<<std::endl;
	}*/

/***** TEST ENVIRONMENT *****/

	//Création du sol
	Object* ground = new Object("ground", "cube", Ogre::Vector3(200,1,200), 0);
	ground->entity()->setMaterialName("Cube");
	m_statics.push_back(ground);
 
 	//Création des pinguins
    for(int i=0; i<20; i++) {
		//std::cout << "i " << i << std::endl;
        Cube* cube = new Cube("penguin" + Ogre::StringConverter::toString(i), "penguin", Ogre::Vector3(10,10,10), 40);
        cube->rigidBody( )->translate(btVector3(rand( )%20-10, rand( )%100+50, rand( )%20-10));
       	m_cubes.push_back(cube);
    }

    /*****CEGUI*****/
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
 
	Ogre::ResourceGroupManager::getSingleton( ).initialiseAllResourceGroups( );
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

/***** END OF TEST ENVIRONMENT *****/

	return true;
}

bool llm::Level::cubeHit( int x, int y ) {
	llm::Application* app = llm::Application::getInstance();
	Ogre::Real xNormalized = static_cast<Ogre::Real>(x) / static_cast<Ogre::Real>( app->window()->getWidth() );
	Ogre::Real yNormalized = static_cast<Ogre::Real>(y) / static_cast<Ogre::Real>( app->window()->getHeight() );
	Ogre::Ray ray = app->camera()->getCameraToViewportRay( xNormalized, yNormalized );

	if( m_indiceCubeSelected == -1 ) { // No cube selected
		for( int i = 0 ; i < m_cubes.size() ; ++i ) {
			if( ray.intersects( m_cubes[i]->sceneNode()->_getWorldAABB() ).first) { 
				m_indiceCubeSelected = i;
				m_cubes[i]->selectCube();
				return true;
			}
		}

	}
	else {
		m_cubes[m_indiceCubeSelected]->releaseCube();
		m_indiceCubeSelected = -1;
	}
	return false;
}

void llm::Level::cubeNextPosition( int x, int y ) {
	llm::Application* app = llm::Application::getInstance();
	Ogre::Real xNormalized = static_cast<Ogre::Real>(x) / static_cast<Ogre::Real>( app->window()->getWidth() );
	Ogre::Real yNormalized = static_cast<Ogre::Real>(y) / static_cast<Ogre::Real>( app->window()->getHeight() );
	Ogre::Ray ray = app->camera()->getCameraToViewportRay( xNormalized, yNormalized );

	Ogre::Vector3 position = ray.getPoint( ray.intersects( plane() ).second );
	m_cubes[m_indiceCubeSelected]->move( position );
}

bool llm::Level::loop() {
	//Simuler l'application ( met à jours les corps )
	llm::Application* app = llm::Application::getInstance();
    app->world()->stepSimulation(1.f/60, 10);
    //updateMagnetism();

	return true;
}