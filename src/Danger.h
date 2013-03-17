#pragma once
#ifndef DANGER_H
#define DANGER_H

#include "Object.h"

namespace llm {
	class Danger : public Object {
	private:
		

	public:
		Danger( const Ogre::String& name, const Ogre::String& mesh, btDynamicsWorld* world, Ogre::SceneManager* sceneManager, Ogre::Vector3& dim, float mass );
		virtual ~Danger( );

		virtual void onCollision( );
	};
}

#endif