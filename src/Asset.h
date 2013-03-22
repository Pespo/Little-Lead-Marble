#ifndef ASSET_H
#define ASSET_H

#include <Ogre.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
 
#include "MotionState.h"
 
namespace llm {
	
	class Asset {

	protected:
		//Ogre::SceneManager* m_pSceneManager;
		Ogre::Entity* m_pEntity;
		Ogre::SceneNode* m_pNode;
		Ogre::Vector3 m_pHalfdim;
        
	public:
		Asset(const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim = Ogre::Vector3(1., 1., 1.));
		Asset( Ogre::SceneNode* node, Ogre::Vector3& dim = Ogre::Vector3(1., 1., 1.), Ogre::Entity* ent = 0);
		~Asset();
 
		inline Ogre::SceneNode* node() {
			return m_pNode;
		}

		inline void position(Ogre::Vector3 position) { m_pNode->setPosition(position); }
		inline void position(int x, int y, int z) { position(Ogre::Vector3(x, y, z)); }
		inline Ogre::Vector3 position() { return m_pNode->getPosition(); }

		inline void orientation(Ogre::Quaternion rotation) { m_pNode->setOrientation(rotation); }
		inline Ogre::Quaternion orientation() { return m_pNode->getOrientation(); }

		inline Ogre::Entity* entity() {
			return m_pEntity;
		}

		inline std::string assetName(){
			return m_pNode->getName();
		}
        

	};
}
#endif