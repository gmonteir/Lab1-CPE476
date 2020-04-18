#pragma once

#ifndef MOVEMENT_CONTROLLER_INCLUDED
#define MOVEMENT_CONTROLLER_INCLUDED

#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "src/Components/Movement.h"

class MovementController {

public:

	MovementController();
	virtual ~MovementController();

	static std::shared_ptr<MovementController> instance;
	
	std::vector<Movement> movementComponents;
	void update();

};

#endif