#pragma once

#ifndef TRANSFORM_CONTROLLER_INCLUDED
#define TRANSFORM_CONTROLLER_INCLUDED

#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "../Components/Transform.h"

class TransformController {

	static std::shared_ptr<TransformController> instance;
	TransformController() {};

public:

	static shared_ptr<TransformController> getInstance();

	std::vector<shared_ptr<Transform>> transformComponents;
	void TransformController::addComponent(shared_ptr<Transform>& transform);

};

#endif