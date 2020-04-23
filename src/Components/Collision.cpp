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

void Collision::update()
{
	vector<shared_ptr<Transform>> comps = TransformController::getInstance()->transformComponents;
	
	for (int i = 0; i < comps.size(); i++) {
		if (distance(transform->position, comps[i]->position) < radius) {
			isColliding = true;
		}
	}
}
