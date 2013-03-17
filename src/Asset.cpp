#include "Asset.h"
#include <Ogre.h>

llm::Asset::Asset( const Ogre::String& name, const Ogre::String& mesh, Ogre::SceneManager* sceneManager, Ogre::Vector3& dim) : m_pSceneManager(sceneManager){

    m_pHalfdim = dim * 1/50.f;
    m_pEntity = m_pSceneManager->createEntity(name + "_ent", mesh + ".mesh");
    m_pNode = m_pSceneManager->getRootSceneNode( )->createChildSceneNode(name + "_node");
    m_pNode->attachObject(m_pEntity);
    m_pNode->scale(m_pHalfdim);
}
 
// llm::Asset::~Asset( ) 
// }
 
Ogre::SceneNode* llm::Asset::sceneNode( ) {
    return m_pNode;
}
 
Ogre::Entity* llm::Asset::entity( ) {
    return m_pEntity;
}