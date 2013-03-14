#pragma once
#ifndef MOTIONSTATE_H
#define MOTIONSTATE_H

#include <LinearMath/btMotionState.h>

namespace llm {

	class MotionState: public btMotionState {

	protected:
		Ogre::SceneNode* m_pNode;
		btTransform m_transform;	

	public:
		/**
		* MotionState
		* @Pespo
		* @param [node] : [Ogre node, position of object]
		*/
		MotionState(Ogre::SceneNode* node) {
			m_pNode = node;
			m_transform.setIdentity( );
		}
		virtual ~MotionState( ) { }

		/**
		* getWorldTransform
		* @Pespo
		* @param [worldTrans] : [Reference to a variable for get the current transform]
		* @return [void] : []
		*/
		virtual void getWorldTransform(btTransform &worldTransform) const {
			worldTransform = m_transform;
		}

		/**
		* setWorldTransform
		* @Pespo
		* @param [worldTrans] : [New transform to set the current transform]
		* @return [void] : []
		*/
		virtual void setWorldTransform(const btTransform &worldTrans) {
			m_transform = worldTrans;
			btQuaternion ori = m_transform.getRotation( );
			btVector3 pos = m_transform.getOrigin( );
			m_pNode->setPosition(Ogre::Vector3(pos.x( ),pos.y( ),pos.z( )));
			m_pNode->setOrientation(Ogre::Quaternion(ori.w( ),ori.x( ),ori.y( ),ori.z( )));
		}
	};
}
#endif