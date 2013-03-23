#include "Player.h"
#include "Tools.h"

const float llm::Player::step = 0.1;
const float llm::Player::vitMax = 10;

llm::Player::Player() : m_pMagnet(Ogre::String( "player" ), Ogre::String( "sphere.mesh" ), MARBLE, Ogre::Vector3(1.,1.,1.), 50) {
	m_pStartingPosition = Ogre::Vector3( 0., 10., 0.); //Default position (0,0,0);
	position(btVector3( 0., 10., 0.));
	m_vitesse = btVector3( 0., 0., 0. );
}

llm::Player::~Player() {
	//if( m_pMagnet ) delete m_pMagnet;
}

void llm::Player::move() {
	std::cout << " vitesse  " << vitesse() << std::endl;
	if(m_direction == L && m_vitesse.getZ() > - vitMax) {
		m_vitesse.setZ( m_vitesse.getZ() < 0 ? m_vitesse.getZ() - step : - step );
	} else if( m_direction == R && m_vitesse.getZ() < vitMax)
		m_vitesse.setZ( m_vitesse.getZ() > 0 ? m_vitesse.getZ() + step : step );
	else if( m_direction == NONE )
		m_vitesse.setZ( 0 );
	m_pMagnet.body()->applyTorqueImpulse( m_vitesse );
}

void llm::Player::init( btVector3& startingPosition, Ogre::Vector3 scale, int mass, bool isNorth) {
	//m_pMagnet = Magnet( Ogre::String( "player" ), Ogre::String( "sphere.mesh" ), MARBLE, scale, mass, isNorth);
	m_pStartingPosition = convert(startingPosition);
	position(startingPosition);
}

void llm::Player::init( Ogre::Vector3 startingPosition, Ogre::Vector3 scale, int mass, bool isNorth) {
	//m_pMagnet = Magnet( Ogre::String( "player" ), Ogre::String( "sphere.mesh" ), MARBLE, scale, mass, isNorth);
	m_pStartingPosition = startingPosition;
	position(convert(startingPosition));
}