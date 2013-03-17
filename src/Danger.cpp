#include "Danger.h"

llm::Danger::Danger( const Ogre::String& name, const Ogre::String& mesh, btDynamicsWorld* world, Ogre::SceneManager* sceneManager, Ogre::Vector3& dim, float mass ) :
 Object( name, mesh, world, sceneManager, dim, mass ) {

}

llm::Danger::~Danger( ) {

}

void llm::Danger::onCollision( ) {
	//TODO: restart level
}