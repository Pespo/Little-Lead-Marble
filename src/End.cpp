#include "End.h"

llm::End::End( const Ogre::String& name, const Ogre::String& mesh, btDynamicsWorld* world, Ogre::SceneManager* sceneManager, Ogre::Vector3& dim, float mass ) :
 Object( name, mesh, world, sceneManager, dim, mass ) {
 	assert(world != NULL);

}

llm::End::~End( ) {

}

void llm::End::onCollision( ) {
	//TODO: Level finished, load next level!
}