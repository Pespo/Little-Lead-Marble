#include "Cube.h"

#include <cmath>
#include "Tools.h"

#include <LinearMath/btVector3.h>

#ifndef M_PI
   #define M_PI 3.14159265358979323846
#endif

llm::Cube::Cube( const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim, float mass ) :
 Object( name, mesh, dim, mass ), m_distanceMax(50), m_force(10.f) {
 	body()->setActivationState(DISABLE_DEACTIVATION);
 	//setPoles(convert(dim), (btConvexHullShape*)m_pShape); 
}

llm::Cube::~Cube() { }

// gets the indice of the nearest vertex of the aproximative position given
int llm::Cube::getNearestVertex( const btVector3& pos, btConvexHullShape* shape, float epsilon ) {
	btVector3 ifPoint;
	for( int i = 0 ; i < shape->getNumVertices() ; ++i ) {
		shape->getVertex(i, ifPoint);
		if( ( ifPoint.getX() >= pos.getX()-epsilon && ifPoint.getX() <= pos.getX()+epsilon ) &&
			( ifPoint.getY() >= pos.getY()-epsilon && ifPoint.getY() <= pos.getY()+epsilon ) )
			return i;
	}
	return -1;
}

// Sets 4 indices from the mesh corresponding to the 4 points we need to define the 2 poles (north & south)
void llm::Cube::setPoles( const btVector3& dim, btConvexHullShape* shape ) {
	btVector3 testPoint;
	btVector3 ifPoint;
	btVector3 northPoint;
	btVector3 southPoint;

	shape->getVertex( 0, testPoint );

	m_indicePoints[NORTH_POINT] = getNearestVertex(-dim, shape, 0.05);
	m_indicePoints[NORTH_POINT2] = getNearestVertex(btVector3(-dim.getX(), dim.getY(), 0), shape, 0.05);
	m_indicePoints[SOUTH_POINT] = getNearestVertex(dim, shape, 0.05);
	m_indicePoints[SOUTH_POINT2] = getNearestVertex(btVector3(dim.getX(), -dim.getY(), 0), shape, 0.05);

}

void llm::Cube::onCollision() {
	//Keep that empty
}

// Stocks a transformation of a rotation and applies it
void llm::Cube::rotateLeft() {
	btTransform transformation;
	transformation.setIdentity();
	btQuaternion rotation;
	rotation.setEuler( 0, 0, M_PI/2 );
	transformation.setRotation(rotation);
	btTransform actualTransformation = body()->getCenterOfMassTransform();
	transformation *= actualTransformation;
	body()->setCenterOfMassTransform( transformation);
}

// Stocks a transformation of a rotation and applies it
void llm::Cube::rotateRight() {
	btTransform transformation;
	transformation.setIdentity();
	btQuaternion rotation;
	rotation.setEuler( 0, 0, 3*M_PI/2 );
	transformation.setRotation(rotation);
	btTransform actualTransformation = body()->getCenterOfMassTransform();
	transformation *= actualTransformation;
	body()->setCenterOfMassTransform( transformation );
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

void llm::Cube::relativeToWorld(int i, btConvexHullShape* shape, btVector3& v) {

	shape->getVertex(i, v);

	//Getting world tansformations
	float yaw, pitch, roll;
	body()->getCenterOfMassTransform().getBasis().getEulerYPR( yaw, pitch, roll );
	yaw *= 180/M_PI; // Values between 0 and pi/2 seem to be signed wrong...

	btVector3 translation = body()->getCenterOfMassPosition();

	//Compute new point position
	float relativeX = v.getX();
	float relativeY = v.getY();
	v.setX(cos( yaw ) * relativeX - sin( yaw ) * relativeY );
	v.setY(sin( yaw ) * relativeX + cos( yaw ) * relativeY );
	v += translation;
	v.setZ(0);

}

// Returns the indice in the mesh of the nearest point from marble
PointRef llm::Cube::nearestMagnetPoint( const btVector3& marble, btConvexHullShape* shape ) {
	float distanceTest = m_distanceMax;
	float nearestDistance = m_distanceMax;
	PointRef nearest = UNKNOWN;
	btVector3 temp;

	for( int i = 0 ; i < 4 ; ++i ) {
		relativeToWorld( m_indicePoints[i], shape, temp );		
		distanceTest = btDistance( marble, temp );
		if( distanceTest < nearestDistance ) {
			nearestDistance = distanceTest;
			nearest = (PointRef)i;
		}
	}

	return nearest;
}

// Computes and returns the orthogonal point of the marble on the pole vector
btVector3 llm::Cube::ortho( const btVector3& marble, const btVector3& point, const btVector3& point2 ) {

	btVector3 pointMarble( marble.getX()-point.getX(), marble.getY()-point.getY(), 0 );
	btVector3 pointPoint2( point2.getX()-point.getX(), point2.getY()-point.getY(), 0 );
	float dot = btDot( pointMarble, pointPoint2 );

	if( dot < 0 )
		return btVector3(999,999,999);

	float distPointPoint2 = btDistance( point, point2 );
	if( distPointPoint2 == 0 )
		return btVector3(999,999,999);
	
	float distPointOrthoPoint = dot/distPointPoint2;
	if( distPointOrthoPoint > distPointPoint2 ) 
		return btVector3(999,999,999);

	float coef = distPointOrthoPoint/distPointPoint2;
	return btVector3( point.getX() + coef * pointPoint2.getX(), point.getY() + coef * pointPoint2.getY(), 0 );
}

btVector3 llm::Cube::getNormal( const btVector3& magnetVector ) {
	return ( magnetVector.cross( btVector3( 0, 0, 1 ) ) ).normalize();
}

// Computes and returns the magnetic force to apply on the marble
btVector3 llm::Cube::getMagneticForce( const btVector3& marble ) {
	btVector3 forcePoint;
	btConvexHullShape* shape = static_cast<btConvexHullShape*>(body()->getCollisionShape()); // Cast to be able to use getVertex function

	PointRef nearestPointI = nearestMagnetPoint( marble, shape );

	if( nearestPointI == UNKNOWN ) {
		return btVector3( 0, 0, 0 );
	}

	btVector3 originPoint; // Defines the 1st point to build pole vector
	btVector3 complementaryPoint; // Defines the complementary point

	switch(nearestPointI) {
		case NORTH_POINT: 	shape->getVertex(m_indicePoints[nearestPointI], originPoint); // Gets the correct mesh point thanks to its indice stocked in setPoles
							relativeToWorld(m_indicePoints[nearestPointI], shape, originPoint); // Transforms mesh point to world object point
							shape->getVertex(m_indicePoints[NORTH_POINT2], complementaryPoint);
							relativeToWorld(m_indicePoints[NORTH_POINT2], shape, complementaryPoint);
							break;
		case NORTH_POINT2: 	shape->getVertex(m_indicePoints[NORTH_POINT], originPoint);
							relativeToWorld(m_indicePoints[NORTH_POINT], shape, originPoint);		
							shape->getVertex(m_indicePoints[nearestPointI], complementaryPoint);
							relativeToWorld(m_indicePoints[nearestPointI], shape, complementaryPoint);
							break;
		case SOUTH_POINT: 	shape->getVertex(m_indicePoints[nearestPointI], originPoint);
							relativeToWorld(m_indicePoints[nearestPointI], shape, originPoint);
							shape->getVertex(m_indicePoints[SOUTH_POINT2], complementaryPoint);
							relativeToWorld(m_indicePoints[SOUTH_POINT2], shape, complementaryPoint);
							break;
		case SOUTH_POINT2: 	shape->getVertex(m_indicePoints[SOUTH_POINT], originPoint);
							relativeToWorld(m_indicePoints[SOUTH_POINT], shape, originPoint);
							shape->getVertex(m_indicePoints[nearestPointI], complementaryPoint);
							relativeToWorld(m_indicePoints[nearestPointI], shape, complementaryPoint);
							break;
		default: break;
	}

	forcePoint = ortho( marble, originPoint, complementaryPoint );

	if( forcePoint.getZ() == 999 ) { // Marble not concerned by the magnet
		return btVector3( 0, 0, 0 );
	}

	if( nearestPointI == NORTH_POINT || nearestPointI == NORTH_POINT2 ) {
		return -((marble-forcePoint).normalize()*m_force / ( forcePoint ).distance2( marble )); 
	}

	if( nearestPointI == SOUTH_POINT || nearestPointI == SOUTH_POINT2 ) {
		return (marble-forcePoint).normalize()*m_force / ( forcePoint ).distance2( marble );
	}

}