#pragma once
#ifndef CUBE_H
#define CUBE_H

#include <Ogre.h>

#include "Object.h"
#include "Magnet.h"

namespace llm {
	class Cube : public Object {
	private:
		bool m_bIsGhost;
		std::vector<Magnet*> m_magnets;

		void onClick( );
		virtual void onCollision( );

	public:
		Cube( const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim, float mass );
		Cube( Ogre::SceneNode* sNode, Ogre::Entity* ent, float mass );
		virtual ~Cube( );

		void rotate( );
		void move( Ogre::Vector3 p );

		inline bool isGhost() {
			return m_bIsGhost;
		}

		inline void isGhost(bool b) {
			m_bIsGhost = b;
		}
	};
}

#endif