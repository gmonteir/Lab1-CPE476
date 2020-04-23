#include "MovementController.h"

shared_ptr<MovementController> MovementController::getInstance()
{
	static shared_ptr<MovementController> instance(new MovementController);
	return instance;
}

void MovementController::update()
{
	for (size_t i = 0; i < movementComponents.size(); i++)
	{
		if (movementComponents[i] != nullptr) movementComponents[i]->update();
	}
}

void MovementController::addComponent(shared_ptr<Movement>& movement)
{
	movementComponents.push_back(movement);
}
