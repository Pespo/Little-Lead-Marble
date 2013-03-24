#include "Level.h"
#include "Application.h"
#include "DotSceneLoader.h"

llm::Level::Level() : m_startingPosition( Ogre::Vector3( 0, 0, 0 ) ), m_plane( Ogre::Vector3( 0, 0, 1 ), Ogre::Vector3( 0, 0, 0 ) ),
						m_bIsMagnetized( false ), m_bIsEnded( false ), m_bIsWon( false ) {
	//m_pEnd = new End();
}

llm::Level::~Level() {
	deleteLevel();
}

bool llm::Level::load() {
	// //FUNCTION LOADING A SCENE FROM XML FILE
	llm::Application* app = llm::Application::getInstance();
	DotSceneLoader loader; 
	loader.loadScene("../res/3dsmax/level_2/level2.xml");

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
	/*Object* ground = new Object("ground", "cube.mesh", Ogre::Vector3(100, 1 ,2), 0);
	ground->entity()->setMaterialName("ground");
	ground->position(btVector3(0., -10., 0.));
	addObject(ground);

	// //std::cout << "i " << i << std::endl;
	Object* leftWall = new Object("leftWall", "cube.mesh", Ogre::Vector3(1,1,1), 0);
    leftWall->entity()->setMaterialName("cube");
    leftWall->position(btVector3(-20, 12, 0.));
   	addObject(leftWall);

   	Cube* rightWall = new Cube("rightWall", "cube.mesh", Ogre::Vector3(1,1,1), 50);
    rightWall->entity()->setMaterialName("cube");
    rightWall->position(btVector3(20, 12, 0.));
   	addCube(rightWall);*/

   	/*Magnet* magnet = new Magnet("magnet", "cube.mesh", UP, Ogre::Vector3( 10, 0.2, 1 ), 0, false);
   	magnet->entity()->setMaterialName("cube");
    magnet->position(btVector3(0., 40., 0.));
   	addMagnet(magnet);

   	Magnet* magnet2 = new Magnet("magnet2", "cube.mesh", DOWN, Ogre::Vector3( 10, 0.2, 1 ), 0, false);
   	magnet2->entity()->setMaterialName("cube");
    magnet2->position(btVector3(0., 1.5, 0.));
   	addMagnet(magnet2);

   	Magnet* magnet3 = new Magnet("magnet3", "cube.mesh", LEFT, Ogre::Vector3( 0.2, 5, 1 ), 0, false);
   	magnet3->entity()->setMaterialName("cube");
    magnet3->position(btVector3(10., 7, 0.));
   	addMagnet(magnet3);

   	Magnet* magnet4 = new Magnet("magnet4", "cube.mesh", RIGHT, Ogre::Vector3( 0.2, 5, 1 ), 0, false);
   	magnet4->entity()->setMaterialName("cube");
    magnet4->position(btVector3(-10, 7, 0.));
   	addMagnet(magnet4);*/

   	/*Object* livre = new Object("etagere", "etagere.mesh", Ogre::Vector3(10,10,10), 0);
   	livre->entity()->setMaterialName("etagere");
    livre->position(btVector3(5,8, 1.));
   	addObject(livre);*/
	return true;
}

void llm::Level::deleteLevel() {
	deleteStatic();
	deleteObject();
	deleteCube();
	deleteMagnet();
	deleteDanger();
	deleteLight();
	//delete m_pEnd();
}

void llm::Level::deleteStatic() {
	for( size_t i = 0; i < m_statics.size(); i++ )
        delete m_statics[i];
    m_statics.clear();
}
void llm::Level::deleteObject() {
	for( size_t i = 0; i < m_objects.size(); i++ )
        delete m_objects[i];
    m_objects.clear();
}
void llm::Level::deleteCube() {
	for(size_t i=0; i<m_cubes.size(); i++)
        delete m_cubes[i];
    m_cubes.clear();
}
void llm::Level::deleteMagnet(){
	for( size_t i = 0; i < m_magnets.size(); i++ )
        delete m_magnets[i];
    m_magnets.clear();
}
void llm::Level::deleteDanger() {
	for( size_t i = 0; i < m_dangers.size(); i++ )
        delete m_dangers[i];
    m_dangers.clear();
}
void llm::Level::deleteLight() {
	llm::Application::getInstance()->game()->sceneManager()->destroyAllLights();
	m_lights.clear();
}