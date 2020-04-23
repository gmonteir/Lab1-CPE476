#pragma once

#ifndef MOVEMENT_CONTROLLER_INCLUDED
#define MOVEMENT_CONTROLLER_INCLUDED

#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "../Components/Movement.h"

class MovementController {

	static std::shared_ptr<MovementController> instance;
	MovementController() {};

public:

	static shared_ptr<MovementController> getInstance();
	
	std::vector<shared_ptr<Movement>> movementComponents;
	void update();
	void MovementController::addComponent(shared_ptr<Movement>& movement);

};

#endif