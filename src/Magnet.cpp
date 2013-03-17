#include "Magnet.h"

llm::Magnet::Magnet( const Ogre::String& name, const Ogre::String& mesh, btDynamicsWorld* world, Ogre::SceneManager* sceneManager, Ogre::Vector3& dim, float mass, bool north ) :
 Object( name, mesh, world, sceneManager, dim, mass ), m_bIsNorth(north) {

}

llm::Magnet::~Magnet( ) {

}

void llm::Magnet::onCollision( ) {
	//Keep that empty
}