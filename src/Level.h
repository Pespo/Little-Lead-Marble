#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <Ogre.h>

#include "Player.h"
#include "Object.h"
#include "Cube.h"
#include "Magnet.h"
#include "Danger.h"
#include "End.h"

namespace llm {
	class Level {
	private:
		Player* m_pPlayer;
		Ogre::Vector3 m_startPosition;
		std::vector<Asset*> m_statics;
		std::vector<Object*> m_objects;
		std::vector<Cube*> m_cubes;
		std::vector<Magnet*> m_magnets;
		std::vector<Danger*> m_dangers;
		End* m_pEnd;
		bool m_bIsMagnetized;
		bool m_bIsEnded;
		bool m_bIsWon;

	public:
		Level( );
		~Level( );

		inline Player* player( ) {
			return m_pPlayer;
		}

		inline void setPlayer( Player* p ) {
			m_pPlayer = p;
		}

		inline Ogre::Vector3 startPosition( ) {
			return m_startPosition;
		}

		inline void setStartPosition( Ogre::Vector3 sP ) {
			m_startPosition = sP;
		}

		inline std::vector<Asset*> statics( ) {
			return m_statics;
		}

		inline void setStatics( std::vector<Asset*> s ) {
			m_statics = s;
		}

		//Add one static
		inline void addStatic(Asset *s){ 
			m_statics.push_back(s);
		}

		inline std::vector<Cube*> cubes( ) {
			return m_cubes;
		}

		inline void setCubes( std::vector<Cube*> c ) {
			m_cubes = c;
		}

		//Add a cube
		inline void addCube( Cube* c ) {
			m_cubes.push_back(c);
		}


		inline std::vector<Magnet*> magnets( ) {
			return m_magnets;
		}

		inline void setMagnets( std::vector<Magnet*> m ) {
			m_magnets = m;
		}

		//Add a magnet
		inline void addMagnet( Magnet* m ) {
			m_magnets.push_back(m);
		}

		inline std::vector<Danger*> dangers( ) {
			return m_dangers;
		}

		inline void setDangers( std::vector<Danger*> d ) {
			m_dangers = d;
		}

		//Add a danger
		inline void addDanger(Danger* d){
			m_dangers.push_back(d);
		}

		inline End* end( ) {
			return m_pEnd;
		}

		inline void setEnd( End* pE ) {
			m_pEnd = pE;
		}

		inline bool isMagnetized( ) {
			return m_bIsMagnetized;
		}

		inline void setIsMagnetized( bool bIM ) {
			m_bIsMagnetized = bIM;
		}

		inline bool isEnded( ) {
			return m_bIsEnded;
		}

		inline void setIsEnded( bool bIE ) {
			m_bIsEnded = bIE;
		}

		inline bool isWon( ) {
			return m_bIsWon;
		}

		inline void setIsWon( bool bIW ) {
			m_bIsWon = bIW;
		}

	};
}

#endif