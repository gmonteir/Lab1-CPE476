#include "Collision.h"

#include "../Controllers/MovementController.h"

Collision::Collision(shared_ptr<Transform> transform, shared_ptr<Movement> movement, float radius)
{
	Collision::transform = transform;
	Collision::movement = movement;
	Collision::radius = radius;
	Collision::isColliding = false;
}

Collision::~Collision()
{
}

void Collision::update()
{
	vector<shared_ptr<Movement>> comps = MovementController::getInstance()->movementComponents;
	
	for (int i = 0; i < comps.size(); i++) {
		if (distance(transform->position, comps[i]->transform->position) < radius) {
			isColliding = true;

			//float oldX = movement->velocity.x * -1;
			//float oldZ = movement->velocity.z * -1;

			//float olX = comps[i]->velocity.x * -1;
			//float olZ = comps[i]->velocity.z * -1;

			//movement->setVelocity(vec3(oldX, 0, oldZ));
			//comps[i]->setVelocity(vec3(olX, 0, olZ));

		}
	}

	//if (transform->position.x == 25 || transform->position.x == -25) {
	//	movement->setVelocity(vec3(movement->velocity.x * -1, 0, movement->velocity.z));
	//}

	//if (transform->position.z == 25 || transform->position.z == -25) {
	//	movement->setVelocity(vec3(movement->velocity.x, 0, movement->velocity.z * -1));
	//}
}
