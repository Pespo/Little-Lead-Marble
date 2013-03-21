#ifndef ASSET_H
#define ASSET_H

#include <Ogre.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
 
#include "MotionState.h"
 
namespace llm {
	
	class Asset {

	protected:
		Ogre::SceneManager* m_pSceneManager;
		Ogre::Entity* m_pEntity;
		Ogre::SceneNode* m_pNode;
		Ogre::Vector3 m_pHalfdim;
        
	public:
		Asset(const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim);
		Asset( Ogre::SceneNode* node, Ogre::Vector3& dim, Ogre::Entity* ent = 0);
		~Asset();
 
		Ogre::SceneNode* sceneNode();
		Ogre::Entity* entity();

		inline std::string getAssetName(){
			return  m_pNode->getName();
		}
        

	};
}
#endif