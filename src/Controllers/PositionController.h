#pragma once

#ifndef POSITION_CONTROLLER_INCLUDED
#define POSITION_CONTROLLER_INCLUDED

#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "src/Components/Position.h"

class PositionController {

public:

	PositionController();
	virtual ~PositionController();

	static std::shared_ptr<PositionController> instance;

	std::vector<Position> positionComponents;
	void update();

};

#endif