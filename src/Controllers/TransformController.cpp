#include "TransformController.h"

TransformController::TransformController()
{
	if (instance == nullptr)
	{
		instance = make_shared<TransformController>();
	}
}

TransformController::~TransformController()
{
	if (instance)
	{
		instance = nullptr;
	}
}

void TransformController::addComponent(shared_ptr<Transform>& transform)
{
	transformComponents.push_back(transform);
}