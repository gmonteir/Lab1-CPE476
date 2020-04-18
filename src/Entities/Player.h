#pragma once

#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include <memory>
#include "src/Components/Movement.h"
#include "src/Components/Position.h"
#include "src/Components/Collision.h"

class Player {

public:
	
	Player();
	virtual ~Player();
	
	std::shared_ptr<Movement> movementComponent;
	std::shared_ptr<Position> positionComponent;
	std::shared_ptr<Collision> collisionComponent;

};

#endif