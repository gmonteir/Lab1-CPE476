#include "CollisionController.h"


shared_ptr<CollisionController> CollisionController::getInstance()
{
	static shared_ptr<CollisionController> instance(new CollisionController);
	return instance;
}

void CollisionController::update()
{
	for (size_t i = 0; i < collisionComponents.size(); i++)
	{
		if (collisionComponents[i] != nullptr) collisionComponents[i]->update();
	}
}

void CollisionController::addComponent(shared_ptr<Collision>& collision)
{
	collisionComponents.push_back(collision);
}
