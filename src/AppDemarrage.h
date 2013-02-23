#include <Ogre.h>
 
class AppDemarrage {

public:
    AppDemarrage();
    ~AppDemarrage();
 
    bool start();
	void createFrameListener();
	//void createScene();
 
private:
    Ogre::Root *mRoot;
    Ogre::RenderWindow* mWindow;
    Ogre::Camera* mCamera;
	Ogre::SceneManager* mSceneMgr;
};