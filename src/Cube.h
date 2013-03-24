#pragma once
#ifndef CUBE_H
#define CUBE_H

#include "Object.h"
#include "Magnet.h"

#include <Ogre.h>
#include <LinearMath/btVector3.h>

enum PointRef {
	NORTH_POINT,
	NORTH_POINT2,
	SOUTH_POINT,
	SOUTH_POINT2,
	UNKNOWN
};

namespace llm {
	class Cube : public Object {
	private:
		const float m_distanceMax;
		float m_force;
		int m_indicePoints[4];

		virtual void onCollision();

		void relativeToWorld(int i, btConvexHullShape* shape, btVector3& v);
		int getNearestVertex( const btVector3& pos, btConvexHullShape* shape, float epsilon=0 );
		void setPoles( const btVector3& dim, btConvexHullShape* shape );
		
		PointRef nearestMagnetPoint( const btVector3& marble, btConvexHullShape* shape );
		btVector3 ortho( const btVector3& marble, const btVector3& point, const btVector3& point2 );
		btVector3 getNormal( const btVector3& magnetVector );
		

	public:
		Cube( const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim, float mass=0 );
		virtual ~Cube( );

		void rotateLeft();
		void rotateRight();
		void move( Ogre::Vector3 position );
		btVector3 getMagneticForce( btVector3& point );
	};
}

#endif