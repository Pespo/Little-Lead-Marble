#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Magnet.h"

namespace llm {
	class Player {
	private:
		Magnet* m_pMagnet;
		Object* m_pObject;
		Ogre::Vector3 m_startingPosition;

	public:
		Player( );
		Player( const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim, float mass, bool north) ;
		~Player( );

		void goLeft( );
		void goRight( );

		inline Magnet* magnet( ) {
			return m_pMagnet;
		}

		inline void setMagnet( Magnet* pM ) {
			m_pMagnet = pM;
		}

		inline void switchPole( ) {
			m_pMagnet->setIsNorth( !( m_pMagnet->isNorth() ) );
		}

		//set the player's current position 
		inline void setPosition( Ogre::Vector3 &v ) {
			if(m_pMagnet->sceneNode())
				m_pMagnet->sceneNode()->setPosition(v);
		}


		//return the player's current position (i.e the ball magnet's node position)
		inline Ogre::Vector3 getPosition( ) {
			return m_pMagnet->sceneNode()->getPosition();
		}


		//set the player's starting position (one for each level)
		inline void setStartingPosition( Ogre::Vector3 v ) {
			m_startingPosition = v;
		}

		//set the player's starting position (one for each level)
		inline Ogre::Vector3 getStartingPosition() {
			return m_startingPosition;
		}

		//reset position
		inline void resetPosition() {
			m_pMagnet->sceneNode()->setPosition(m_startingPosition);
		}
	};
}

#endif