#pragma once

#ifndef MOVEMENT_INCLUDED
#define MOVEMENT_INCLUDED

#include <glm\glm.hpp>
#include <memory>
#include "Transform.h"

using namespace glm;
using namespace std;

class Movement {

public:

	Movement(shared_ptr<Transform> transform);
	Movement(shared_ptr<Transform> transform, vec3 velocity);
	virtual ~Movement();

	shared_ptr<Transform> transform;
	vec3 velocity;

	virtual void update();
	void setVelocity(vec3 velocity);

};

#endif