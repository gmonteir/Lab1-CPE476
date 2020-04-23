#include "MovementController.h"

MovementController::MovementController()
{
	if (instance == nullptr)
	{
		instance = make_shared<MovementController>();
	}
}

MovementController::~MovementController()
{
	if (instance)
	{
		instance = nullptr;
	}
}

void MovementController::update()
{
	for (size_t i = 0; i < movementComponents.size; i++)
	{
		movementComponents[i]->update();
	}
}

void MovementController::addComponent(shared_ptr<Movement>& movement)
{
	movementComponents.push_back(movement);
}
