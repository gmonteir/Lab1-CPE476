#include "Player.h"


using namespace std;

Player::Player(vec3 position, float radius) {
	
	Player::transformComponent = make_shared<Transform>(position);
	Player::collisionComponent = make_shared<Collision>(transformComponent, radius);
	
	TransformController::getInstance()->addComponent(transformComponent);
	MovementController::getInstance()->addComponent(movementComponent);
	CollisionController::getInstance()->addComponent(collisionComponent);
}

Player::~Player()
{
}



