#include "Player.h"

llm::Player::Player( ) 
{
	m_pMagnet = NULL;
	m_startingPosition = Ogre::Vector3(0.0); //Default position (0,0,0);
	
}

llm::Player::Player( btVector3&  startPosition ) {
	m_pMagnet = new Magnet( Ogre::String("player"), Ogre::String("bille"), MARBLE, Ogre::Vector3(10,10,10), 10., true, 50);
	m_pMagnet->body()->translate(startPosition);
}


llm::Player::~Player( ) {
	if(m_pMagnet) delete m_pMagnet;
}

void llm::Player::addImpulse( btVector3& impulse ) {
	m_pMagnet->body()->applyCentralImpulse(impulse);
}


void llm::Player::goLeft( ) {
	addImpulse(btVector3(-100., 0., 0.));
	std::cout << " test L-------- " << std::endl;
}

void llm::Player::goRight( ) {
	addImpulse(btVector3(0., 0., 100.));
	std::cout << " test R-------- " << std::endl;
}