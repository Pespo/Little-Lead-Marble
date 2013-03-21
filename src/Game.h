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
        btSimpleDynamicsWorld* m_pWorld;

		llm::Level* m_pLevel;
		llm::Player* m_pPlayer;

	public :
		Game();
		~Game();	

		void loadLevel();
		void loop();
		bool cubeHit( int x, int y );
		void cubeNextPosition( float x, float y );

		inline Ogre::SceneManager* sceneManager(){
            return m_pSceneManager;
        } 
        inline btSimpleDynamicsWorld* world(){
            return m_pWorld;
        } 
        inline Ogre::Camera* camera(){
            return m_pCamera;
        } 
        inline llm::Level* level(){
            return m_pLevel;
        } 

	};
}

#endif