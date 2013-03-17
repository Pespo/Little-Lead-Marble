#pragma once
#ifndef END_H
#define END_H

#include "Object.h"

namespace llm {
	class End : public Object {
	private:
		

	public:
		End( const Ogre::String& name, const Ogre::String& mesh, btDynamicsWorld* world, Ogre::SceneManager* sceneManager, Ogre::Vector3& dim, float mass );
		virtual ~End( );

		virtual void onCollision( );
	};
}

#endif