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
 
#include "Asset.h"
#include "MotionState.h"
 
namespace llm {
	class Object : public Asset {

	protected:
		btDynamicsWorld* m_pWorld;
        
		btCollisionShape* m_pShape;
		btRigidBody* m_pBody;

	public:
		Object( const Ogre::String& name, const Ogre::String& mesh, btDynamicsWorld* world, Ogre::SceneManager* sceneManager, Ogre::Vector3& dim, float mass );
		~Object(); 
 
		btRigidBody* rigidBody( );
        
		void getMeshInformation( Ogre::MeshPtr mesh, size_t &vertex_count,Ogre::Vector3* &vertices,
			size_t &index_count, unsigned* &indices,
			const Ogre::Vector3 &scale = Ogre::Vector3::UNIT_SCALE,
			const Ogre::Vector3 &position = Ogre::Vector3::ZERO,
			const Ogre::Quaternion &orient = Ogre::Quaternion::IDENTITY );
	};
}
#endif