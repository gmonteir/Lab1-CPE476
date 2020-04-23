#pragma once

#ifndef COLLISION_CONTROLLER_INCLUDED
#define COLLISION_CONTROLLER_INCLUDED

#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "../Components/Collision.h"

class CollisionController {

	static std::shared_ptr<CollisionController> instance;
	CollisionController() {};

public:

	static shared_ptr<CollisionController> getInstance();

	std::vector<shared_ptr<Collision>> collisionComponents;
	void update();
	void CollisionController::addComponent(shared_ptr<Collision>& collision);

};

#endif