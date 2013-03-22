#pragma once
#ifndef DANGER_H
#define DANGER_H

#include "Object.h"

namespace llm {
	class Danger : public Object {
	private:
		

	public:
		Danger( const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim, float mass );
		Danger( Ogre::SceneNode* sNode, Ogre::Vector3& dim, Ogre::Entity* ent, float mass );
		virtual ~Danger( );

		virtual void onCollision( );
	};
}

#endif