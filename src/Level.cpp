#include "Level.h"
#include "Application.h"

llm::Level::Level( ) {
	m_bIsMagnetized = false;
	m_bIsEnded = false;
	m_bIsWon = false;	
}

llm::Level::~Level( ) {
	for(int i=0; i<m_statics.size( ); i++)
        delete m_statics[i];
    m_statics.clear( );
    for(int i=0; i<m_objects.size( ); i++)
        delete m_objects[i];
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

	//delete m_pEnd;

}

void llm::Level::load() {

	srand(time(NULL));
	//Création du sol
	Object* ground = new Object("ground", "cube", llm::Application::getInstance()->game()->world(), llm::Application::getInstance()->game()->sceneManager(), Ogre::Vector3(200,1,200), 0);
	m_objects.push_back(ground);
 
 	//Création des pinguins
    for(int i=0; i<20; i++) {
		//std::cout << "i " << i << std::endl;
        Object* cube = new Object("penguin" + Ogre::StringConverter::toString(i), "penguin", llm::Application::getInstance()->game()->world(), llm::Application::getInstance()->game()->sceneManager(), Ogre::Vector3(10,10,10), 40);
        cube->rigidBody( )->translate(btVector3(rand( )%20-10, rand( )%100+50, rand( )%20-10));
       	m_objects.push_back(cube);
    }
}

bool llm::Level::loop() {
	return true;
}