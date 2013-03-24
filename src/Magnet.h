#ifndef MAGNET_H
#define MAGNET_H

#include "Object.h"

enum Orientation {
	UP, RIGHT, DOWN, LEFT, MARBLE
};

namespace llm {
	class Magnet : public Object {

	protected:
		Orientation m_orientation;
		bool m_bIsNorth;
		float m_force;
		const float m_distanceMax;

	public:

		Magnet( const Ogre::String& name, const Ogre::String& mesh, Orientation orientation, Ogre::Vector3& dim = Ogre::Vector3(1., 1., 1.), float mass = 0, bool north = false, int force = 1000);
		~Magnet();

		virtual void onCollision();

		btVector3 getMagneticForce( const btVector3& marble );
		btVector3 ortho( const btVector3& marble, const btVector3& point, const btVector3& point2 );


		inline bool isNorth() { return m_bIsNorth; }
		inline void isNorth( bool bIN ) { m_bIsNorth = bIN; }
		inline int force() { return m_force; }
		inline void force( int force ) { m_force = force; }
	};
}

#endif