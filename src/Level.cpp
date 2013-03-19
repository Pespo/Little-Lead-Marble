#include "Level.h"
#include "Application.h"

llm::Level::Level( ) : m_startPosition( Ogre::Vector3( 0, 0, 0 ) ), m_plane( Ogre::Vector3( 0, 0, 1 ), Ogre::Vector3( 0, 0, 0 ) ),
						m_indiceCubeSelected(-1), m_bIsMagnetized( false ), m_bIsEnded( false ), m_bIsWon( false ) {
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
	srand(time(NULL));
	//Création du sol
	Object* ground = new Object("ground", "cube", Ogre::Vector3(200,1,200), 0);
	//ground->entity()->setMaterialName("Cube");
	m_objects.push_back(ground);
 
 	//Création des pinguins
    for(int i=0; i<20; i++) {
		//std::cout << "i " << i << std::endl;
        Cube* cube = new Cube("penguin" + Ogre::StringConverter::toString(i), "penguin", Ogre::Vector3(10,10,10), 40);
        cube->rigidBody( )->translate(btVector3(rand( )%20-10, rand( )%100+50, rand( )%20-10));
       	m_cubes.push_back(cube);
    }

	return true;
}

bool llm::Level::loop() {
	return true;
}