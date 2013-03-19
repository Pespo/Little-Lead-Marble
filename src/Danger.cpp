#include "Danger.h"

llm::Danger::Danger( const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim, float mass ) :
 Object( name, mesh, dim, mass ) {

}

//Constructor called in DotSceneLoader
llm::Danger::Danger(Ogre::SceneNode* sNode, Ogre::Entity* ent) : 
Object(sNode, ent) {

}

llm::Danger::~Danger( ) {

}

void llm::Danger::onCollision( ) {
	//TODO: restart level
}