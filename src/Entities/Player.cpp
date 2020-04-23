#include "Player.h"

using namespace std;

Player::Player(vec3 position, float radius) {
	
	Player::transformComponent = make_shared<Transform>(position);
	Player::movementComponent = make_shared<Movement>(transformComponent);
	Player::collisionComponent = make_shared<Collision>(transformComponent, movementComponent, radius);

	Player::transformComponent->setRadius(radius);
	/*Player::transformComponent->parent = (GameObject*)(this);
	Player::movementComponent->parent = (GameObject*)(this);
	Player::collisionComponent->parent = (GameObject*)(this);*/
	
	TransformController::getInstance()->addComponent(transformComponent);
	MovementController::getInstance()->addComponent(movementComponent);
	CollisionController::getInstance()->addComponent(collisionComponent);

}

Player::~Player()
{
}



