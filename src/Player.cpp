#include "Player.h"

llm::Player::Player( ) 
{
	m_pMagnet = NULL;
	m_startingPosition = Ogre::Vector3(0.0); //Default position (0,0,0);
	
}


llm::Player::~Player( ) {
	if(m_pMagnet)delete m_pMagnet;
}

void llm::Player::goLeft( ) {

}

void llm::Player::goRight( ) {

}