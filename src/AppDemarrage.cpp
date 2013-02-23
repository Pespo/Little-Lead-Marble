#include "AppDemarrage.h"
#include "InputListener.h"

AppDemarrage::AppDemarrage() : mRoot(0) {
	//Définition du root(fichier de plugins à charger, fichier de configuration d'Ogre, fichier de log).
	mRoot = new Ogre::Root("../res/plugins.cfg", "../res/resources.cfg", "../res/Ogre.log");
	Ogre::RenderSystem *rs = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
	mRoot->setRenderSystem(rs);
	rs->setConfigOption("Full Screen", "No");
	rs->setConfigOption("Video Mode", "1280 x 800 @ 32-bit colour");
	rs->setConfigOption("VSync", "Yes");
	
	mWindow = mRoot->initialise(true, "Little Lead Marble");
	mSceneMgr = mRoot->createSceneManager("DefaultSceneManager", "Default Scene Manager");
	mCamera = mSceneMgr->createCamera("PlayerCam");

	createFrameListener();
}

AppDemarrage::~AppDemarrage() {
    delete mRoot;
}

bool AppDemarrage::start() {	
	//Chargement des ressources
	Ogre::ConfigFile configFile;
	configFile.load("../res/resources.cfg"); //Permet de charger les ressources
	Ogre::ConfigFile::SectionIterator seci = configFile.getSectionIterator(); //iterteur qui va permettre de parcourir le fichier ressource.cfg
	Ogre::String secName, typeName, archName;
	while (seci.hasMoreElements()) {
		secName = seci.peekNextKey();
		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;
		for (i = settings->begin(); i != settings->end(); ++i) {
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
		}
	}
	

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

	mCamera->setPosition(Ogre::Vector3(0,0,100));
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(5);
 
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
 
	Ogre::Entity *ent = mSceneMgr->createEntity("pinguin", "penguin.mesh");
	Ogre::SceneNode *node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	node->attachObject(ent);

	//createScene();
	createFrameListener();

	while(true)	{
		Ogre::WindowEventUtilities::messagePump();
		if(mWindow->isClosed())
			return false; 
  
		if(!mRoot->renderOneFrame())
			return false;
	}

	return true;
}

void AppDemarrage::createFrameListener() {
    Ogre::FrameListener* mInputListener = new InputListener(mWindow, mCamera, mSceneMgr);
    mRoot->addFrameListener(mInputListener);
}