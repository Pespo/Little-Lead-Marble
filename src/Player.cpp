#include "Player.h"
#include "Tools.h"

const float llm::Player::step = 0.01;
const float llm::Player::vitMax = 0.05;

llm::Player::Player() : Magnet(Ogre::String( "player" ), Ogre::String( "sphere.mesh" ), MARBLE, Ogre::Vector3( .002, .002, .002), 1) {
	m_pStartingPosition = Ogre::Vector3( 0., 10., 0.); //Default position (0,0,0);
	entity()->setMaterialName("bille.material");
	position(btVector3( 0., 10., 0.));
	m_vitesse = btVector3( 0., 0., 0. );
	body()->setActivationState(DISABLE_DEACTIVATION);
	body()->setFriction(50);
}

llm::Player::~Player() { }

void llm::Player::move() {
	//std::cout << " vitesse  " << vitesse() << std::endl;
	if(m_direction == R && m_vitesse.getZ() > - vitMax) {
		m_vitesse.setZ( m_vitesse.getZ() < 0 ? m_vitesse.getZ() - step : - step );
	} else if( m_direction == L && m_vitesse.getZ() < vitMax)
		m_vitesse.setZ( m_vitesse.getZ() > 0 ? m_vitesse.getZ() + step : step );
	else if( m_direction == NONE )
		m_vitesse.setZ( 0 );
	body()->applyTorqueImpulse( m_vitesse );
}

llm::Player* llm::Player::init( btVector3& startingPosition, bool isNorth ) {
	return init( convert(startingPosition) );
}

llm::Player* llm::Player::init( Ogre::Vector3 startingPosition, bool isNorth ) {
	m_pStartingPosition = startingPosition;
	position(convert(startingPosition));
	llm::Magnet::isNorth(isNorth);
	body()->setAngularVelocity(btVector3(0,0,0));
	body()->setLinearVelocity(btVector3(0,0,0));
	return this;
}