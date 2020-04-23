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
			if (distance(transform->position, comps[i]->transform->position) < radius*2) {
				isColliding = true;
				
				if (comps[i]->transform->radius == 1 && !(movement->isFrozen))
				{
					TransformController::getInstance()->numCollected++;
					int num = TransformController::getInstance()->numCollected;
					
					movement->setVelocity(vec3(0, 0, 0));
					movement->isFrozen = true;

					cout << "Object collected! Score: ";
					cout << num;
					cout << endl;
				}
				else
				{
					float bounceX = movement->velocity.x * -1;
					float bounceZ = movement->velocity.z * -1;

					movement->setVelocity(vec3(bounceX, 0, bounceZ));
				}

			}
		}
	}

	//cout << transform->position.x << endl;

	if (transform->position.x >= 50 || transform->position.x <= -50) {
		movement->setVelocity(vec3(movement->velocity.x * -1, 0, movement->velocity.z));
	}

	if (transform->position.z >= 50 || transform->position.z <= -50) {
		movement->setVelocity(vec3(movement->velocity.x, 0, movement->velocity.z * -1));
	}
}
