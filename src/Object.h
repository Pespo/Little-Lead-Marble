#pragma once
#ifndef OBJECT_H
#define OBJECT_H
 
#include <btBulletDynamicsCommon.h>
#include <Bullet-C-Api.h>
#include <btBulletCollisionCommon.h>
#include <LinearMath\btVector3.h>

#include <Ogre.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
 
#include "MotionState.h"
 
namespace llm {
	class Object {
	protected:
		btDynamicsWorld* m_pWorld;
		Ogre::SceneManager* m_pSceneManager;
 
		Ogre::Entity* m_pEntity;
		Ogre::SceneNode* m_pNode;
        
		btCollisionShape* m_pShape;
		btRigidBody* m_pBody;

		bool m_bHasPhysics;

	public:
		Object( const Ogre::String& name, const Ogre::String& mesh, btDynamicsWorld* world, Ogre::SceneManager* sceneManager, Ogre::Vector3& dim, float mass );
		virtual ~Object();
 
		btRigidBody* rigidBody( );
		Ogre::SceneNode* sceneNode();
		Ogre::Entity* entity();
		bool hasPhysics();
        
		void getMeshInformation( Ogre::MeshPtr mesh, size_t &vertex_count,Ogre::Vector3* &vertices,
			size_t &index_count, unsigned* &indices,
			const Ogre::Vector3 &scale = Ogre::Vector3::UNIT_SCALE,
			const Ogre::Vector3 &position = Ogre::Vector3::ZERO,
			const Ogre::Quaternion &orient = Ogre::Quaternion::IDENTITY );
	};
}
#endif