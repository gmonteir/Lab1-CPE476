#pragma once

#ifndef TRANSFORM_CONTROLLER_INCLUDED
#define TRANSFORM_CONTROLLER_INCLUDED

#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "../Components/Transform.h"

class TransformController {

public:

	TransformController();
	virtual ~TransformController();

	static std::shared_ptr<TransformController> instance;

	std::vector<Transform> transformComponents;
	void update();

};

#endif