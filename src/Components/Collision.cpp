#include "Collision.h"

Collision::Collision(shared_ptr<Transform> transform, float radius)
{
	Collision::transform = transform;
	Collision::radius = radius;
	Collision::isColliding = false;
}

Collision::~Collision()
{
}

void Collision::update(vector<shared_ptr<Collision>> worldObjects)
{
	for (int i=0; i < worldObjects.size; i++) {
		if (distance(transform->position, worldObjects[i]->transform->position) < radius) {
			isColliding = true;
		}
	}
}
