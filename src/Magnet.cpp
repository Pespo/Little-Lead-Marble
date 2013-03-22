#include "Magnet.h"

llm::Magnet::Magnet( const Ogre::String& name, const Ogre::String& mesh, Orientation orientation, Ogre::Vector3& dim, float mass, bool north, int force) :
 Object( name, mesh, dim, mass ), m_orientation(orientation), m_bIsNorth(north), m_force(north ? -1 * force : force) {} 

//Constructor called in DotSceneLoader
llm::Magnet::Magnet(Ogre::SceneNode* sNode, Ogre::Vector3& dim, Ogre::Entity* ent, float mass, bool north) : 
Object(sNode, dim, ent, mass),  m_bIsNorth(north) {}

llm::Magnet::~Magnet( ) {

}

void llm::Magnet::onCollision( ) {
	//Keep that empty
}