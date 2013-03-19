#include "Magnet.h"

llm::Magnet::Magnet( const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim, float mass, bool north ) :
 Object( name, mesh, dim, mass ), m_bIsNorth(north) {

}

//Constructor called in DotSceneLoader
llm::Magnet::Magnet(Ogre::SceneNode* sNode, Ogre::Entity* ent, float mass, bool north) : 
Object(sNode, ent, mass),  m_bIsNorth(north) {

}

llm::Magnet::~Magnet( ) {

}

void llm::Magnet::onCollision( ) {
	//Keep that empty
}