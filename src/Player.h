#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Magnet.h"
#include "Singleton.h"

enum Direction { L, R, NONE };

namespace llm {
	class Player : public Magnet, public Singleton<Player> {	

		friend class Singleton<Player>;	

		Player();
		~Player();

		Ogre::Vector3 m_pStartingPosition;
		btVector3 m_vitesse;
		Direction m_direction;

	public:
		static const float step;
		static const float vitMax;

		llm::Player* init( btVector3& startingPosition, bool isNorth = false);
		llm::Player* init( Ogre::Vector3 startingPosition, bool isNorth = false);
		void move();

		inline Direction direction() { return m_direction; }
		inline void direction(Direction direction) { m_direction = direction; }

		inline void vitesse( float vitesse ) { m_vitesse = btVector3( 0., 0., vitesse ); }
		inline float vitesse() { return m_vitesse.getZ(); }

		inline bool isNorth() { return m_bIsNorth; }
		inline void isNorth( bool bIN ) { m_bIsNorth = bIN; }
		inline void switchPole() { isNorth( !isNorth() ); }

		inline void startingPosition( Ogre::Vector3 startingPosition ) { m_pStartingPosition = startingPosition; position( startingPosition );}
		inline Ogre::Vector3 startingPosition() { return m_pStartingPosition; }
		inline void resetPosition() { position(m_pStartingPosition); }
	};
}

#endif