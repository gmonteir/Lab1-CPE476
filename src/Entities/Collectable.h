#pragma once

#ifndef COLLECTABLE_INCLUDED
#define COLLECTABLE_INCLUDED

#include <memory>
#include "src/Components/Movement.h"
#include "src/Components/Position.h"
#include "src/Components/Collision.h"
#include "src/Components/Render.h"

class Collectable {

public:

	Collectable();
	virtual ~Collectable();
	
	std::shared_ptr<Movement> movementComponent;
	std::shared_ptr<Position> positionComponent;
	std::shared_ptr<Collision> collisionComponent;
	std::shared_ptr<Render> renderComponent;

};

#endif