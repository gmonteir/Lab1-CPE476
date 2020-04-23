#pragma once

#ifndef COLLISION_INCLUDED
#define COLLISION_INCLUDED

#include <glm\glm.hpp>
#include <memory>
#include <vector>
#include <iostream>
#include "Component.h"
#include "Transform.h"
#include "Movement.h"
#include "../Controllers/TransformController.h"

using namespace std;
using namespace glm;

class Collision : public Component {

public:

	Collision(shared_ptr<Transform> transform, shared_ptr<Movement> movement, float radius);
	virtual ~Collision();

	virtual void update();

	bool isColliding;
	bool isPlayer;
	shared_ptr<Transform> transform;
	shared_ptr<Movement> movement;
	float radius;

};

#endif