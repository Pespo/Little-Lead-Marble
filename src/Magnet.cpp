#include "Magnet.h"

#include "Tools.h"

llm::Magnet::Magnet( const Ogre::String& name, const Ogre::String& mesh, Orientation orientation, Ogre::Vector3& dim, float mass, bool north, int force) :
 Object( name, mesh, dim, mass ), m_orientation(orientation), m_bIsNorth(north), m_distanceMax(50), m_force(north ? -1 * force : force) { }
 	

llm::Magnet::~Magnet() {

}

void llm::Magnet::onCollision() {
	//Keep that empty
}

// Computes and returns the orthogonal point of the marble on the pole vector
btVector3 llm::Magnet::ortho( const btVector3& marble, const btVector3& point, const btVector3& point2 ) {

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

// Computes and returns the magnetic force to apply on the marble
btVector3 llm::Magnet::getMagneticForce( const btVector3& marble ) {
	btVector3 minimum = convert( node()->_getWorldAABB().getMinimum() );
	btVector3 maximum = convert( node()->_getWorldAABB().getMaximum() );
	minimum.setZ(0);
	maximum.setZ(0);

	if( btDistance( marble, minimum ) < m_distanceMax || btDistance( marble, maximum ) < m_distanceMax ) {
		if( m_orientation == DOWN || m_orientation == LEFT ) {
			btVector3 tmp = maximum;
			maximum = minimum;
			minimum = tmp;
		}
			
		btVector3 forcePoint = ortho( marble, minimum, maximum );
		if( forcePoint.getZ() == 999 ) { // Marble not concerned by the magnet
			return btVector3( 0, 0, 0 );
		}

		if( m_bIsNorth )
			return -((marble-forcePoint).normalize()*m_force / ( forcePoint ).distance2( marble )); 
		else
			return (marble-forcePoint).normalize()*m_force / ( forcePoint ).distance2( marble );
	}
	return btVector3( 0, 0, 0 );
}