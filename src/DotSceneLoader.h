#ifndef DOT_SCENELOADER_H
#define DOT_SCENELOADER_H
 
// Includes
#include <Ogre.h>
#include <OgreString.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include <OgreResourceGroupManager.h>
#include <vector>
 
#include "rapidxml.hpp"
 
    class DotSceneLoader
    {
    public:
 
        DotSceneLoader();
        virtual ~DotSceneLoader();
 
		void loadScene(const Ogre::String &SceneName);

 
    protected:
    
        void processNode(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent = 0);
		void processBallStartPosition(rapidxml::xml_node<>* XMLNode);

 
        Ogre::String getAttrib(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, const Ogre::String &defaultValue = "");
        Ogre::Real getAttribReal(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, Ogre::Real defaultValue = 0);
        bool getAttribBool(rapidxml::xml_node<>* XMLNode, const Ogre::String &parameter, bool defaultValue = false);
 
        Ogre::Vector3 parseVector3(rapidxml::xml_node<>* XMLNode);
        Ogre::Quaternion parseQuaternion(rapidxml::xml_node<>* XMLNode);
        Ogre::ColourValue parseColour(rapidxml::xml_node<>* XMLNode);
 
    };
 
#endif // DOT_SCENELOADER_H