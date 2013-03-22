#pragma once
#ifndef CUBE_H
#define CUBE_H

#include <Ogre.h>

#include "Object.h"
#include "Magnet.h"

namespace llm {
	class Cube : public Object {
	private:
		bool m_bIsGhost; // Useless? Level stocks the indice of the selected Cube (-1 if no Cube selected)
		Magnet* m_pNorthMagnet;
		Magnet* m_pSouthMagnet;

		virtual void onCollision( );

	public:
		Cube( const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim, float mass=0 );
		virtual ~Cube( );

		void rotate( );
		void move( Ogre::Vector3 position );
		void selectCube();
		void releaseCube();

		inline bool isGhost() {
			return m_bIsGhost;
		}

		inline void setIsGhost(bool b) {
			m_bIsGhost = b;
		}
	};
}

#endif