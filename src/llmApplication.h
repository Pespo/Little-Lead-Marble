#ifndef __llmApplication_h_
#define __llmApplication_h_

#include "llmObject.h"

#include <Ogre.h>
#include <btBulletDynamicsCommon.h>
#include <Bullet-C-Api.h>
#include <btBulletCollisionCommon.h>
 
class llmApplication {

public:
    llmApplication();
    ~llmApplication();
 
    bool start();
    void exit();
	void createFrameListener();
 
private:
    //Variable ogre3d
    Ogre::Root *m_Root;
    Ogre::RenderWindow* m_Window;
    Ogre::Camera* m_Camera;
	Ogre::SceneManager* m_SceneMgr;
    Ogre::FrameListener* m_InputListener;

    //variable bullet
	btDbvtBroadphase* m_broadphase;
    btDefaultCollisionConfiguration* m_collisionConfiguration;
    btCollisionDispatcher* m_dispatcher;
    btSequentialImpulseConstraintSolver* m_solver;
    btDiscreteDynamicsWorld* m_world;

    //autre
	std::vector<llmObject*> m_objectList;
    bool m_ShutDown;
};

#endif