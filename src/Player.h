#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Magnet.h"

namespace llm {
	class Player {
	private:
		Magnet* m_pMagnet;

	public:
		Player( );
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
			m_pMagnet->setIsNorth( !( m_pMagnet->isNorth( ) ) );
		}


	};
}

#endif