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
		if (transform != comps[i]->transform)
		{
			if (distance(transform->position, comps[i]->transform->position) < radius) {
				isColliding = true;

				/*float oldX = movement->velocity.x * -1;
				float oldZ = movement->velocity.z * -1;

				float olX = comps[i]->velocity.x * -1;
				float olZ = comps[i]->velocity.z * -1;*/

				movement->setVelocity(vec3(0, 0, 0));
				comps[i]->setVelocity(vec3(0, 0, 0));

			}
		}
	}

	if (transform->position.x == 50 || transform->position.x == -50) {
		movement->setVelocity(vec3(movement->velocity.x * -1, 0, movement->velocity.z));
	}

	if (transform->position.z == 50 || transform->position.z == -50) {
		movement->setVelocity(vec3(movement->velocity.x, 0, movement->velocity.z * -1));
	}
}
