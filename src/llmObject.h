#ifndef _OBJECT_H_
#define _OBJECT_H_
 
#include <btBulletDynamicsCommon.h>
#include <Bullet-C-Api.h>
#include <btBulletCollisionCommon.h>
#include <LinearMath\btVector3.h>

#include <Ogre.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
 
#include "llmMotionState.h"
#include "llmObject.h"
 
class llmObject {

    public:
        llmObject(const Ogre::String& name, const Ogre::String& mesh, btDynamicsWorld* world, Ogre::SceneManager* smgr, Ogre::Vector3& dim, float mass);
        virtual ~llmObject();
 
        btRigidBody* getRigidBody();
        Ogre::SceneNode* getSceneNode();
        Ogre::Entity* getEntity();
		void getMeshInformation(Ogre::MeshPtr mesh, size_t &vertex_count,Ogre::Vector3* &vertices,
		  size_t &index_count, unsigned* &indices,
          const Ogre::Vector3 &scale = Ogre::Vector3::UNIT_SCALE,
		  const Ogre::Vector3 &position = Ogre::Vector3::ZERO,
		  const Ogre::Quaternion &orient = Ogre::Quaternion::IDENTITY);
 
    protected:
        btDynamicsWorld* m_world;
        Ogre::SceneManager* m_smgr;
 
        Ogre::Entity* m_ent;
        Ogre::SceneNode* m_node;
        
        btCollisionShape* m_shape;
        btRigidBody* m_body;
        
        btVector3* m_verticesTest;
};

#endif