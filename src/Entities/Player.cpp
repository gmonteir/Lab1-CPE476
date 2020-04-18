#include "Player.h"

using namespace std;

Player::Player() {
	Player::movementComponent = make_shared<Movement>();
	Player::positionComponent = make_shared<Position>();
	Player::collisionComponent = make_shared<Collision>();
}