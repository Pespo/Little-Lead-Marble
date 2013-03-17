#pragma once
#ifndef MAGNET_H
#define MAGNET_H

#include "Object.h"

namespace llm {
	class Magnet : public Object {
	protected:
		bool m_bIsNorth;

	public:
		Magnet( const Ogre::String& name, const Ogre::String& mesh, btDynamicsWorld* world, Ogre::SceneManager* sceneManager, Ogre::Vector3& dim, float mass, bool north );
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