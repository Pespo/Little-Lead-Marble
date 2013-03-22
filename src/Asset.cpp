#include "Asset.h"
#include <Ogre.h>
#include "Application.h"

llm::Asset::Asset( const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim) {
	m_pSceneManager = llm::Application::getInstance()->game()->sceneManager();
    m_pHalfdim = dim * 1/50.f;
    m_pEntity = m_pSceneManager->createEntity(name + "_ent", mesh + ".mesh");
    m_pNode = m_pSceneManager->getRootSceneNode( )->createChildSceneNode(name + "_node");
    m_pNode->attachObject(m_pEntity);
    m_pNode->scale(m_pHalfdim);
}

llm::Asset::Asset( Ogre::SceneNode* sNode, Ogre::Vector3& dim, Ogre::Entity* ent) {
    m_pNode = sNode;
	m_pEntity = ent;
	m_pHalfdim = dim;
	//if(static_cast<Ogre::Entity*>(m_pNode->getAttachedObject(0))) m_pEntity = static_cast<Ogre::Entity*>(m_pNode->getAttachedObject(0));
}
 
llm::Asset::~Asset( ) {
	/*delete m_pNode;
	delete m_pEntity;
	delete m_pSceneManager;*/
}
 

Ogre::SceneNode* llm::Asset::sceneNode( ) {
    return m_pNode;
}
 
Ogre::Entity* llm::Asset::entity( ) {
    return m_pEntity;
}