#include "CollisionController.h"

CollisionController::CollisionController()
{
	if (instance == nullptr)
	{
		instance = make_shared<CollisionController>();
	}
}

CollisionController::~CollisionController()
{
	if (instance)
	{
		instance = nullptr;
	}
}

void CollisionController::update()
{
	for (size_t i = 0; i < collisionComponents.size; i++)
	{
		collisionComponents[i]->update();
	}
}

void CollisionController::addComponent(shared_ptr<Collision>& collision)
{
	collisionComponents.push_back(collision);
}
