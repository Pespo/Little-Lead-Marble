#include "Asset.h"
#include "Application.h"

llm::Asset::Asset( const Ogre::String& name, const Ogre::String& mesh, Ogre::Vector3& dim) {
	Ogre::SceneManager* sceneManager = llm::Application::getInstance()->game()->sceneManager();
    m_pHalfdim = dim * 1/50.f;
    m_pEntity = sceneManager->createEntity(name + "_ent", mesh);
    m_pNode = sceneManager->getRootSceneNode()->createChildSceneNode(name + "_node");
    m_pNode->attachObject(m_pEntity);
    m_pNode->scale(m_pHalfdim); // dim pour la scene
}


llm::Asset::Asset( Ogre::SceneNode* sNode, Ogre::Vector3& dim, Ogre::Entity* ent) {
    m_pNode = sNode;
	m_pEntity = ent;
	m_pHalfdim = dim;

}



llm::Asset::~Asset() { }
