#pragma once

#ifndef MOVEMENT_INCLUDED
#define MOVEMENT_INCLUDED

#include <glm\glm.hpp>

class Movement {

public:

	glm::vec3 velocity;
	virtual void update();

};

#endif