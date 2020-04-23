#pragma once

#ifndef MOVEMENT_CONTROLLER_INCLUDED
#define MOVEMENT_CONTROLLER_INCLUDED

#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "../Components/Movement.h"

class MovementController {

public:

	MovementController();
	virtual ~MovementController();

	static std::shared_ptr<MovementController> instance;
	
	std::vector<shared_ptr<Movement>> movementComponents;
	void update();
	void MovementController::addComponent(shared_ptr<Movement>& movement);

};

#endif