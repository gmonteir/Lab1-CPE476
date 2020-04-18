#pragma once
#include <glm\glm.hpp>

#ifndef MOVEMENT_INCLUDED
#define MOVEMENT_INCLUDED

class Movement {

public:

	glm::vec3 velocity;
	virtual void update();

};

#endif