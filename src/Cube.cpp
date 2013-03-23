#include "Tools.h"
#include "Cube.h"

#include <LinearMath/btVector3.h>

#ifndef M_PI
   #define M_PI 3.14159265358979323846
#endif

llm::Cube::Cube( const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim, float mass ) :
 Object( name, mesh, dim, mass ), m_bIsGhost( false ) { }


llm::Cube::~Cube() { }

void llm::Cube::onCollision() {
	//Keep that empty
}

void llm::Cube::rotateLeft() {
	btTransform transformation;
	transformation.setIdentity();
	btQuaternion rotation;
	rotation.setEuler( 0, 0, M_PI/4 );
	transformation.setRotation(rotation);
	btTransform actualTransformation = body()->getCenterOfMassTransform();
	transformation *= actualTransformation;
	body()->setCenterOfMassTransform( transformation);
}

void llm::Cube::rotateRight() {
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
	btVector3 btPosition = convert( position );
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