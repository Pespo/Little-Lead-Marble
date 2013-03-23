#include "Magnet.h"

llm::Magnet::Magnet( const Ogre::String& name, const Ogre::String& mesh, Orientation orientation, Ogre::Vector3& dim, float mass, bool north, int force) :
 Object( name, mesh, dim, mass ), m_orientation(orientation), m_bIsNorth(north), m_force(north ? -1 * force : force) {} 


llm::Magnet::~Magnet( ) {

}

void llm::Magnet::onCollision( ) {
	//Keep that empty
}