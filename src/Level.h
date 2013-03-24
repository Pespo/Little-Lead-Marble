#pragma once
#ifndef LEVEL_H
#define LEVEL_H

#include "Player.h"
#include "Object.h"
#include "Cube.h"
#include "Magnet.h"
#include "Danger.h"
#include "End.h"

#include <vector>
#include <string>
#include <Ogre.h>

namespace llm {
	class Level {

		Ogre::Vector3 m_startingPosition;
		Ogre::Plane m_plane;
		std::vector<Asset*> m_statics;
		std::vector<Object*> m_objects;
		std::vector<Cube*> m_cubes;
		std::vector<Magnet*> m_magnets;
		std::vector<Danger*> m_dangers;
		std::vector<Ogre::Light*> m_lights;
		End* m_pEnd;
		bool m_bIsMagnetized;
		bool m_bIsEnded;
		bool m_bIsWon;

	public:
		Level();
		~Level();

		bool loop();
		bool load();

		inline Ogre::Plane plane() { return m_plane; }

		inline Ogre::Vector3 startingPosition() { return m_startingPosition; }
		inline void startingPosition( Ogre::Vector3 sP ) { m_startingPosition = sP; }
		inline std::vector<Cube*> cubes() { return m_cubes; }
		inline std::vector<Magnet*> magnets() { return m_magnets; }
		inline void addStatic(Asset *s){ m_statics.push_back(s); }
		inline void addObject( Object* o ) { m_objects.push_back(o); }
		inline void addCube( Cube* c ) { m_cubes.push_back(c); }
		inline void addMagnet( Magnet* m ) { m_magnets.push_back(m); }
		inline void addDanger(Danger* d){ m_dangers.push_back(d); }
		inline void addLight(Ogre::Light* d){ m_lights.push_back(d); }

		void deleteLevel();
		void deleteStatic();
		void deleteObject();
		void deleteCube();
		void deleteMagnet();
		void deleteDanger();
		void deleteLight();

		inline End* end() { return m_pEnd; }
		inline void end( End* pE ) { m_pEnd = pE; }

		inline bool isMagnetized() { return m_bIsMagnetized; }
		inline void isMagnetized( bool bIM ) { m_bIsMagnetized = bIM; }
		
		inline bool isEnded() { return m_bIsEnded; }
		inline void iSEnded( bool bIE ) { m_bIsEnded = bIE; }

		inline bool isWon() { return m_bIsWon;}
		inline void isWon( bool bIW ) { m_bIsWon = bIW; }
	};
}

#endif