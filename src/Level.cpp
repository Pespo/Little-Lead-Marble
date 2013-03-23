#include "Level.h"
#include "Application.h"
#include "DotSceneLoader.h"

llm::Level::Level( ) : m_startPosition( Ogre::Vector3( 0, 0, 0 ) ), m_plane( Ogre::Vector3( 0, 0, 1 ), Ogre::Vector3( 0, 0, 0 ) ),
						m_bIsMagnetized( false ), m_bIsEnded( false ), m_bIsWon( false ) {
	//m_pEnd = new End();
}

llm::Level::~Level( ) {
	for(int i=0; i<m_statics.size( ); i++)
        delete m_statics[i];
    m_statics.clear( );

    for(int i=0; i<m_objects.size( ); i++)
        delete m_objects[i];
    m_objects.clear( );

    for(int i=0; i<m_magnets.size( ); i++)
        delete m_magnets[i];
    m_magnets.clear( );

    for(int i=0; i<m_dangers.size( ); i++)
        delete m_dangers[i];
    m_dangers.clear( );

    for(int i=0; i<m_cubes.size( ); i++)
        delete m_cubes[i];
    m_cubes.clear( );

	//delete m_pEnd;

}

bool llm::Level::load() {
	//Import Scene
	
	//FUNCTION LOADING A SCENE FROM XML FILE
	/*llm::Application* app = llm::Application::getInstance();
	DotSceneLoader loader; 
	loader.loadScene("../res/3dsmax/level_2/level2.xml");
	std::cout<<"start positon"<<app->game()->player()->getStartingPosition().x<<std::endl;*/

	//Verif remplissage lvl
	/*std::vector<Cube*> assetLvl = app->game()->level()->cubes();
	std::cout<<"Vector statics size ::: "<<assetLvl.size()<<std::endl;
	for(int j=0; j<assetLvl.size(); ++j){
		std::cout<<"NODE NAME :"<<assetLvl[j]->getAssetName()<<std::endl;
		std::cout<<"ENTITY NAME :"<<assetLvl[j]->entity()->getName()<<std::endl;
	}*/

	/***** TEST ENVIRONMENT ****/
	srand(time(NULL));
	//Création du sol

	Object* ground = new Object("ground", "cube.mesh", Ogre::Vector3(200,1,200), 0);
	//ground->entity()->setMaterialName("ground");
	m_objects.push_back(ground);

 	//Création des pinguins
    for(int i=0; i<3; i++) {
		//std::cout << "i " << i << std::endl;
		Cube* cube = new Cube("cube" + Ogre::StringConverter::toString(i), "cube.mesh", Ogre::Vector3(10,10,10), 500);
        //cube->entity()->setMaterialName("cube");
        cube->position(btVector3(rand( )%20-10, rand( )%100+50, 0.));
       	m_cubes.push_back(cube);
    }

	//Just to see the "ball player"

	//llm::Application* app = llm::Application::getInstance();
	/*Ogre::SceneNode *node = app->game()->sceneManager()->getRootSceneNode( )->createChildSceneNode("billeT_node");

	Ogre::Entity *enti =  app->game()->sceneManager()->createEntity("billeT", "bille.mesh");
    node->attachObject(enti);
	Magnet* billeT = new Magnet(node, Ogre::Vector3(2.0, 2.0, 2.0),enti, 10, true);
    //bille->rigidBody( )->translate(btVector3(rand( )%20-10, rand( )%100+50, rand( )%20-10));
    m_magnets.push_back(billeT);*/

    m_startPosition = Ogre::Vector3( 0., 20., 0.);

	return true;
}

bool llm::Level::loop() {
	return true;
}