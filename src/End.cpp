#include "End.h"

llm::End::End( const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim, float mass ) :
 Object( name, mesh, dim, mass ) {

}

 //Constructor called in DotSceneLoader
 llm::End::End( Ogre::SceneNode* sNode, Ogre::Entity* ent, float mass ) :
 Object(sNode, ent, mass) {

}

llm::End::~End( ) {

}

void llm::End::onCollision( ) {
	//TODO: Level finished, load next level!
}