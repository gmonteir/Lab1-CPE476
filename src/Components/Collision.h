#pragma once

#ifndef COLLISION_INCLUDED
#define COLLISION_INCLUDED

#include <glm\glm.hpp>
#include <memory>
#include <vector>
#include "Transform.h"

using namespace std;
using namespace glm;

class Collision {

public:

	Collision(shared_ptr<Transform> transform, float radius);
	virtual ~Collision();

	virtual void update(vector<shared_ptr<Collision>> worldObjects);

	bool isColliding;
	shared_ptr<Transform> transform;
	float radius;

};

#endif