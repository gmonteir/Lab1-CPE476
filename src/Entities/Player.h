#pragma once

#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include <memory>
#include "../Components/Movement.h"
#include "../Components/Collision.h"
#include "../Components/Transform.h"

class Player {

public:
	
	Player();
	virtual ~Player();
	
	std::shared_ptr<Movement> movementComponent;
	std::shared_ptr<Transform> transformComponent;
	std::shared_ptr<Collision> collisionComponent;

};

#endif