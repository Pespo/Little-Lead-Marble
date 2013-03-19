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

	public :
		Game();
		~Game();	

		void loadLevel();
		void loop();

		inline Ogre::SceneManager* sceneManager(){
            return m_pSceneManager;
        } 
        inline btDiscreteDynamicsWorld* world(){
            return m_pWorld;
        } 
        inline Ogre::Camera* camera(){
            return m_pCamera;
        } 

	};
}

#endif