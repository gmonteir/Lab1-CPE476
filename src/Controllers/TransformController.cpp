#include "TransformController.h"

shared_ptr<TransformController> TransformController::getInstance()
{
	static shared_ptr<TransformController> instance(new TransformController);
	return instance;
}

void TransformController::addComponent(shared_ptr<Transform>& transform)
{
	transformComponents.push_back(transform);
}