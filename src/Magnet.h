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
		int m_force;

	public:

		Magnet( const Ogre::String& name, const Ogre::String& mesh, Orientation orientation, Ogre::Vector3& dim = Ogre::Vector3(1., 1., 1.), float mass = 0, bool north = false, int force = 1);
		Magnet(Ogre::SceneNode* sNode, Ogre::Vector3& dim, Ogre::Entity* ent, float mass, bool north);

		virtual ~Magnet( );

		virtual void onCollision( );

		inline bool isNorth( ) {
			return m_bIsNorth;
		}

		inline void setIsNorth( bool bIN ) {
			m_bIsNorth = bIN;
		}

		inline int force( ) {
			return m_force;
		}

		inline void force( int force ) {
			m_force = force;
		}
	};
}

#endif