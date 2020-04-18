#pragma once

#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include <memory>
#include "../Components/Movement.h"
#include "../Components/Collision.h"
#include "../Components/Position.h"

class Player {

public:
	
	Player();
	virtual ~Player();
	
	std::shared_ptr<Movement> movementComponent;
	std::shared_ptr<Position> positionComponent;
	std::shared_ptr<Collision> collisionComponent;

};

#endif