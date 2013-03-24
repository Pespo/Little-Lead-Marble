#include "DotSceneLoader.h"
#include "Asset.h"
#include "Application.h"
#include "Object.h"
#include "Cube.h"
#include "Magnet.h"
#include "Danger.h"
#include "End.h"

#pragma warning(disable:4390)
#pragma warning(disable:4305)


DotSceneLoader::DotSceneLoader() { }
DotSceneLoader::~DotSceneLoader() { }

//Parse and load scene from XML file
void DotSceneLoader::loadScene(const Ogre::String &SceneName){
	
	std::ifstream file(SceneName);
    rapidxml::xml_document<> XMLDoc;  
    rapidxml::xml_node<>* XMLRoot;

	if(file){
		std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		buffer.push_back('\0');
		//std::cout<<&buffer[0]<<std::endl; /*test the buffer */
		XMLDoc.parse<0>(&buffer[0]); 

		 // Grab the scene node
		XMLRoot = XMLDoc.first_node("scene");
		//std::cout << "Name of my first node is: " << XMLDoc.first_node()->name() << "\n";  /*test the xml_document */
		 Ogre::String version = getAttrib(XMLRoot, "formatVersion", "unknown");
		 Ogre::String message = "[DotSceneLoader] Parsing dotScene file with version " + version;
		if(XMLRoot->first_attribute("minOgreVersion"))
			message += ", min. Ogre version " + Ogre::String(XMLRoot->first_attribute("minOgreVersion")->value());

		//Ball start position
		rapidxml::xml_node<>* ball;
		ball = XMLRoot->first_node("ball");
		if(ball) processBallStartPosition(ball);
		

	    rapidxml::xml_node<>* pNodes;
		// Process nodes (?)
		pNodes = XMLRoot->first_node("nodes");
		if(pNodes){
			rapidxml::xml_node<>* pNode;
			 // Process node (*)
			pNode = pNodes->first_node("node");
			while(pNode)
			{
				processNode(pNode);
				pNode = pNode->next_sibling("node");
			}
		}
	}
}


//Process ball start position
void DotSceneLoader::processBallStartPosition(rapidxml::xml_node<>* XMLNode) {
	rapidxml::xml_node<>* pElement;
	pElement = XMLNode->first_node("position");
	if(pElement)
	//to do @ add test for player's existance
	llm::Application::getInstance()->game()->level()->startingPosition(parseVector3(pElement));
}

//Process node
void DotSceneLoader::processNode(rapidxml::xml_node<>* XMLNode, Ogre::SceneNode *pParent) {
	//Atributes
	Ogre::String assetType;
	Ogre::String magnetPole;
	Orientation enumPole;
	Ogre::Vector3 position;
	Ogre::Vector3 scale;
	Ogre::Quaternion rotation = Ogre::Quaternion::IDENTITY;
	Ogre::String entityName;
	bool castShadows;
	Ogre::String meshFileName;
    Ogre::String materialFile;


	rapidxml::xml_node<>* pElement;

    // Process type  and magnet pole
    pElement = XMLNode->first_node("type");
    if(pElement){
		assetType = getAttrib(pElement, "name");
		magnetPole = getAttrib(pElement, "pole");
		if (magnetPole.compare("UP") == 0) enumPole = UP;
		else if (magnetPole.compare("RIGHT") == 0)  enumPole = RIGHT;
		else if (magnetPole.compare("DOWN") == 0)  enumPole = DOWN;
		else if (magnetPole.compare("LEFT") == 0)  enumPole = LEFT;
		else enumPole = MARBLE;

	}
        
    // Process position
    pElement = XMLNode->first_node("position");
    if(pElement){
        position = parseVector3(pElement);
	}

	//Process scale
	pElement = XMLNode->first_node("scale");
    if(pElement){
        scale = parseVector3(pElement);
	}

	//Process rotation
	pElement = XMLNode->first_node("rotation");
    if(pElement){
        rotation = parseQuaternion(pElement);
	}

	//Process entity
	pElement = XMLNode->first_node("entity");
    if(pElement){
       entityName = getAttrib(pElement, "name");
	   meshFileName = getAttrib(pElement, "meshFile");
       materialFile = getAttrib(pElement, "materialFile");
       castShadows = getAttribBool(pElement, "castShadows", true);
		//Subentity
		rapidxml::xml_node<>* pSubEntity;
		pSubEntity = pElement->first_node("subentities")->first_node("subentity");
		if(pSubEntity) 
				materialFile = getAttrib(pSubEntity, "materialFile");

	}
    // Create the object
    try
    {
		if (assetType.compare("asset") == 0)
		{
			//std::cout<<"Its an asset "<<std::endl;
			llm::Asset *pAsset = new llm::Asset(entityName, meshFileName, scale);
			pAsset->position(position);
			pAsset->orientation(rotation);
			llm::Application::getInstance()->game()->level()->addStatic(pAsset);
	
		}
		
		else if (assetType.compare("object") == 0)
		{
			llm::Object *pObject = new llm::Object(entityName, meshFileName, scale, 0);
			pObject->position(position);
			pObject->orientation(rotation);
			llm::Application::getInstance()->game()->level()->addObject(pObject);
		}
		
		else if (assetType.compare("cube") == 0)
		{
			llm::Cube *pCube = new llm::Cube(entityName, meshFileName, scale, 100);
			pCube->position(position);
			pCube->orientation(rotation);
			llm::Application::getInstance()->game()->level()->addCube(pCube);
		}

		else if (assetType.compare("magnet") == 0)
		{
			llm::Magnet *pMagnet = new llm::Magnet(entityName, meshFileName, enumPole, scale);
			pMagnet->position(position);
			pMagnet->orientation(rotation);
			llm::Application::getInstance()->game()->level()->addMagnet(pMagnet);
		}
		
		else if (assetType.compare("danger") == 0)
		{
			llm::Danger *pDanger = new llm::Danger(entityName, meshFileName, scale);
			pDanger->position(position);
			pDanger->orientation(rotation);
			llm::Application::getInstance()->game()->level()->addDanger(pDanger);
		}

		else if (assetType.compare("end") == 0)
		{
			//std::cout<<"Its the END !!"<<std::endl;
			llm::End *pEnd = new llm::End(entityName, meshFileName, scale);
			pEnd->position(position);
			pEnd->orientation(rotation);
			llm::Application::getInstance()->game()->level()->end(pEnd);
		}
		else
		{
			//std::cout<<"Its not an asset !!"<<std::endl;
		}
        
		//if(!materialFile.empty())
            //->setMaterialName(materialFile);
    }
    catch(Ogre::Exception &/*e*/)
    {
        Ogre::LogManager::getSingleton().logMessage("[DotSceneLoader] Error loading an entity!");
    }
}



Ogre::String DotSceneLoader::getAttrib(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, const Ogre::String &defaultValue) {
    if(XMLNode->first_attribute(attrib.c_str()))
        return XMLNode->first_attribute(attrib.c_str())->value();
    else
        return defaultValue;
}

Ogre::Real DotSceneLoader::getAttribReal(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, Ogre::Real defaultValue) {
    if(XMLNode->first_attribute(attrib.c_str()))
        return Ogre::StringConverter::parseReal(XMLNode->first_attribute(attrib.c_str())->value());
    else
        return defaultValue;
}

bool DotSceneLoader::getAttribBool(rapidxml::xml_node<>* XMLNode, const Ogre::String &attrib, bool defaultValue) {
    if(!XMLNode->first_attribute(attrib.c_str()))
        return defaultValue;

    if(Ogre::String(XMLNode->first_attribute(attrib.c_str())->value()) == "true")
        return true;

    return false;
}

Ogre::Vector3 DotSceneLoader::parseVector3(rapidxml::xml_node<>* XMLNode) {
    return Ogre::Vector3(
        Ogre::StringConverter::parseReal(XMLNode->first_attribute("x")->value()),
        Ogre::StringConverter::parseReal(XMLNode->first_attribute("y")->value()),
        Ogre::StringConverter::parseReal(XMLNode->first_attribute("z")->value())
    );
}

Ogre::Quaternion DotSceneLoader::parseQuaternion(rapidxml::xml_node<>* XMLNode) {
    //! @todo Fix this crap!

    Ogre::Quaternion orientation;

    if(XMLNode->first_attribute("qx"))
    {
        orientation.x = Ogre::StringConverter::parseReal(XMLNode->first_attribute("qx")->value());
        orientation.y = Ogre::StringConverter::parseReal(XMLNode->first_attribute("qy")->value());
        orientation.z = Ogre::StringConverter::parseReal(XMLNode->first_attribute("qz")->value());
        orientation.w = Ogre::StringConverter::parseReal(XMLNode->first_attribute("qw")->value());
    }
    if(XMLNode->first_attribute("qw"))
    {
        orientation.w = Ogre::StringConverter::parseReal(XMLNode->first_attribute("qw")->value());
        orientation.x = Ogre::StringConverter::parseReal(XMLNode->first_attribute("qx")->value());
        orientation.y = Ogre::StringConverter::parseReal(XMLNode->first_attribute("qy")->value());
        orientation.z = Ogre::StringConverter::parseReal(XMLNode->first_attribute("qz")->value());
    }
    else if(XMLNode->first_attribute("axisX"))
    {
        Ogre::Vector3 axis;
        axis.x = Ogre::StringConverter::parseReal(XMLNode->first_attribute("axisX")->value());
        axis.y = Ogre::StringConverter::parseReal(XMLNode->first_attribute("axisY")->value());
        axis.z = Ogre::StringConverter::parseReal(XMLNode->first_attribute("axisZ")->value());
        Ogre::Real angle = Ogre::StringConverter::parseReal(XMLNode->first_attribute("angle")->value());;
        orientation.FromAngleAxis(Ogre::Angle(angle), axis);
    }
    else if(XMLNode->first_attribute("angleX"))
    {
        Ogre::Vector3 axis;
        axis.x = Ogre::StringConverter::parseReal(XMLNode->first_attribute("angleX")->value());
        axis.y = Ogre::StringConverter::parseReal(XMLNode->first_attribute("angleY")->value());
        axis.z = Ogre::StringConverter::parseReal(XMLNode->first_attribute("angleZ")->value());
        //orientation.FromAxes(&axis);
        //orientation.F
    }
    else if(XMLNode->first_attribute("x"))
    {
        orientation.x = Ogre::StringConverter::parseReal(XMLNode->first_attribute("x")->value());
        orientation.y = Ogre::StringConverter::parseReal(XMLNode->first_attribute("y")->value());
        orientation.z = Ogre::StringConverter::parseReal(XMLNode->first_attribute("z")->value());
        orientation.w = Ogre::StringConverter::parseReal(XMLNode->first_attribute("w")->value());
    }
    else if(XMLNode->first_attribute("w"))
    {
        orientation.w = Ogre::StringConverter::parseReal(XMLNode->first_attribute("w")->value());
        orientation.x = Ogre::StringConverter::parseReal(XMLNode->first_attribute("x")->value());
        orientation.y = Ogre::StringConverter::parseReal(XMLNode->first_attribute("y")->value());
        orientation.z = Ogre::StringConverter::parseReal(XMLNode->first_attribute("z")->value());
    }

    return orientation;
}

Ogre::ColourValue DotSceneLoader::parseColour(rapidxml::xml_node<>* XMLNode) {
    return Ogre::ColourValue(
        Ogre::StringConverter::parseReal(XMLNode->first_attribute("r")->value()),
        Ogre::StringConverter::parseReal(XMLNode->first_attribute("g")->value()),
        Ogre::StringConverter::parseReal(XMLNode->first_attribute("b")->value()),
        XMLNode->first_attribute("a") != NULL ? Ogre::StringConverter::parseReal(XMLNode->first_attribute("a")->value()) : 1
    );
}


