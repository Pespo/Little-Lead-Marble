#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Magnet.h"
#include "Singleton.h"

enum Direction { L, R, NONE };

namespace llm {
	class Player : public Singleton<Player>{	

		friend class Singleton<Player>;	

		Player();
		~Player();

		Magnet m_pMagnet;
		Ogre::Vector3 m_pStartingPosition;
		btVector3 m_vitesse;
		Direction m_direction;

	public:
		static const float step;
		static const float vitMax;

		void init( btVector3& startingPosition, Ogre::Vector3 scale = Ogre::Vector3( 1., 1., 1.), int mass = 20, bool isNorth = false);
		void init( Ogre::Vector3 startingPosition, Ogre::Vector3 scale = Ogre::Vector3( 1., 1., 1.), int mass = 20, bool isNorth = false);
		void move();

		inline Direction direction() { return m_direction; }
		inline void direction(Direction direction) { m_direction = direction; }

		inline void vitesse( float vitesse ) { m_vitesse = btVector3( 0., 0., vitesse ); }
		inline float vitesse() { return m_vitesse.getZ(); }

		inline void switchPole() { m_pMagnet.isNorth( !( m_pMagnet.isNorth() ) ); }
		inline bool isNorth() { return m_pMagnet.isNorth(); }

		inline btVector3& position() { return m_pMagnet.position(); }
		inline void position( btVector3& newPosition) { m_pMagnet.position(newPosition); }

		inline void startingPosition( Ogre::Vector3 startingPosition ) { m_pStartingPosition = startingPosition; }
		inline Ogre::Vector3 startingPosition() { return m_pStartingPosition; }
		inline void resetPosition() { m_pMagnet.node()->setPosition(m_pStartingPosition); }
	};
}

#endif