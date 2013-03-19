#include <LinearMath/btVector3.h>

#include "Cube.h"

inline btVector3 cvt( const Ogre::Vector3 &V ) {
    return btVector3( V.x, V.y, V.z );
}

llm::Cube::Cube( const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim, float mass ) :
 Object( name, mesh, dim, mass ), m_bIsGhost( false ) {

}

//Constructor called in DotSceneLoader
llm::Cube::Cube(Ogre::SceneNode* sNode, Ogre::Entity* ent, float mass) : 
Object(sNode, ent, mass) {

}

llm::Cube::~Cube( ) {

}

void llm::Cube::onCollision( ) {
	//Keep that empty
}

void llm::Cube::rotate( ) {

}

void llm::Cube::move( Ogre::Vector3 position ) {
	//Sets the physical position
	btTransform transform = rigidBody()->getCenterOfMassTransform();
	btVector3 btPosition = cvt( position );
	transform.setOrigin( btPosition );
	rigidBody()->setCenterOfMassTransform(transform);

	//Sets the graphic position
	sceneNode()->setPosition( position );
}

void llm::Cube::selectCube() {
	m_bIsGhost = true;
}

void llm::Cube::releaseCube() {
	m_bIsGhost = false;
}