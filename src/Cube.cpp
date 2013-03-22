#include <LinearMath/btVector3.h>

#include "Cube.h"

#ifndef M_PI
   #define M_PI 3.14159265358979323846
#endif

inline btVector3 cvt( const Ogre::Vector3 &V ) {
    return btVector3( V.x, V.y, V.z );
}

llm::Cube::Cube( const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim, float mass ) :
 Object( name, mesh, dim, mass ), m_bIsGhost( false ) { }

//Constructor called in DotSceneLoader
llm::Cube::Cube(Ogre::SceneNode* sNode,Ogre::Vector3& dim, Ogre::Entity* ent, float mass) : 
Object(sNode, dim, ent, mass) {

}

llm::Cube::~Cube( ) {

}

void llm::Cube::onCollision( ) {
	//Keep that empty
}

void llm::Cube::rotateLeft( ) {
	btTransform transformation;
	transformation.setIdentity();
	btQuaternion rotation;
	rotation.setEuler( 0, 0, M_PI/4 );
	transformation.setRotation(rotation);
	btTransform actualTransformation = body()->getCenterOfMassTransform();
	transformation *= actualTransformation;
	body()->setCenterOfMassTransform(transformation);
}

void llm::Cube::rotateRight( ) {
	btTransform transformation;
	transformation.setIdentity();
	btQuaternion rotation;
	rotation.setEuler( 0, 0, -M_PI/4 );
	transformation.setRotation(rotation);

	btTransform actualTransformation = body()->getCenterOfMassTransform();
	
	transformation *= actualTransformation;
	

	std::cout << transformation.getRotation() << std::endl;

	body()->setCenterOfMassTransform(transformation);

}

void llm::Cube::move( Ogre::Vector3 position ) {
	//Sets the physical position
	btTransform transform = body()->getCenterOfMassTransform();
	btVector3 btPosition = cvt( position );
	transform.setOrigin( btPosition );
	body()->setCenterOfMassTransform(transform);

	//Sets the graphic position
	node()->setPosition( position );
}

void llm::Cube::selectCube() {
	m_bIsGhost = true;
}

void llm::Cube::releaseCube() {
	m_bIsGhost = false;
}