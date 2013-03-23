#pragma once
#ifndef END_H
#define END_H

#include "Object.h"

namespace llm {
	class End : public Object {
	private:
		

	public:
		End( const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim, float mass=0 );
		virtual ~End( );

		virtual void onCollision( );
	};
}

#endif