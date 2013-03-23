#include "End.h"

llm::End::End( const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim, float mass ) :
 Object( name, mesh, dim, mass ) {

}

 
llm::End::~End() {

}

void llm::End::onCollision() {
	//TODO: Level finished, load next level!
}