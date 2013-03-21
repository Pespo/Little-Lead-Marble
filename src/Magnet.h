#ifndef MAGNET_H
#define MAGNET_H

#include "Object.h"

namespace llm {
	class Magnet : public Object {
	protected:
		bool m_bIsNorth;

	public:
		Magnet( const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim, float mass, bool north );
		Magnet(Ogre::SceneNode* sNode, Ogre::Vector3& dim, Ogre::Entity* ent, float mass, bool north);
		virtual ~Magnet( );

		virtual void onCollision( );

		inline bool isNorth( ) {
			return m_bIsNorth;
		}

		inline void setIsNorth( bool bIN ) {
			m_bIsNorth = bIN;
		}
	};
}

#endif