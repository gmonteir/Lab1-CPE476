#include "Player.h"

using namespace std;

Player::Player() {
	Player::movementComponent = make_shared<Movement>();
	Player::transformComponent = make_shared<Transform>();
	Player::collisionComponent = make_shared<Collision>();
}

Player::~Player()
{
}
