#pragma once
#ifndef GAME_H
#define GAME_H

#include "Level.h"
#include "Player.h"

#include <btBulletDynamicsCommon.h>
#include <Bullet-C-Api.h>
#include <btBulletCollisionCommon.h>

namespace llm{

	class Game {

		Ogre::SceneManager* m_pSceneManager;
		Ogre::Camera* m_pCamera;

		btDbvtBroadphase* m_pBroadphase;
        btDefaultCollisionConfiguration* m_pCollisionConfiguration;
        btCollisionDispatcher* m_pDispatcher;
        btSequentialImpulseConstraintSolver* m_pSolver;
        btDiscreteDynamicsWorld* m_pWorld;

		llm::Level* m_pLevel;
		llm::Player* m_pPlayer;

		int m_indiceCubeSelected;

	public :
		Game();
		~Game();	

		void loadLevel();
		void loadPlayer();
		void loop();
		bool cubeHit( int x, int y );
		void cubeNextPosition( int x, int y );

		inline int cubeSelected() {
			return m_indiceCubeSelected;
		}
		inline void cubeSelected(int indice) {
			m_indiceCubeSelected = indice;
		}

		inline Ogre::SceneManager* sceneManager(){
            return m_pSceneManager;
        } 
        inline btDiscreteDynamicsWorld* world(){
            return m_pWorld;
        } 
        inline Ogre::Camera* camera(){
            return m_pCamera;
        } 
        inline llm::Level* level(){
            return m_pLevel;
        } 

		 inline llm::Player* player(){
            return m_pPlayer;
        } 
	};
}

#endif