#pragma once

#ifndef COLLECTABLE_INCLUDED
#define COLLECTABLE_INCLUDED

#include <memory>
#include "../Components/Movement.h"
#include "../Components/Transform.h"
#include "../Components/Collision.h"
#include "../Components/Render.h"

class Collectable {

public:

	Collectable();
	virtual ~Collectable();
	
	std::shared_ptr<Movement> movementComponent;
	std::shared_ptr<Transform> transformComponent;
	std::shared_ptr<Collision> collisionComponent;
	std::shared_ptr<Render> renderComponent;

};

#endif