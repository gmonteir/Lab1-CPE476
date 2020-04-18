#pragma once

#ifndef COLLISION_CONTROLLER_INCLUDED
#define COLLISION_CONTROLLER_INCLUDED

#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "../Components/Collision.h"

class CollisionController {

public:

	CollisionController();
	virtual ~CollisionController();

	static std::shared_ptr<CollisionController> instance;

	std::vector<Collision> collisionComponents;
	void update();

};

#endif