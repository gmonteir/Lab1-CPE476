#pragma once

#ifndef MOVEMENT_INCLUDED
#define MOVEMENT_INCLUDED

#include <glm\glm.hpp>
#include <memory>
#include "Component.h"
#include "Transform.h"

using namespace glm;
using namespace std;

class Movement : public Component {

public:

	Movement(shared_ptr<Transform> transform);
	Movement(shared_ptr<Transform> transform, vec3 velocity);
	Movement(shared_ptr<Transform> transform, vec3 velocity, vec3 rotateSpeed);
	Movement(shared_ptr<Transform> transform, vec3 velocity, vec3 rotateSpeed, vec3 scaleSpeed);
	virtual ~Movement();

	shared_ptr<Transform> transform;
	vec3 velocity;
	vec3 rotateSpeed;
	vec3 scaleSpeed;
	bool isFrozen = false;

	virtual void update();
	void setVelocity(vec3 velocity);
	void setRotateSpeed(vec3 rotateSpeed);
	void setScaleSpeed(vec3 scaleSpeed);
};

#endif