#pragma once

#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

#include <memory>
#include "GameObject.h"
#include "../Components/Movement.h"
#include "../Components/Collision.h"
#include "../Components/Transform.h"
#include "../BaseCode/Shape.h"
#include "../BaseCode/Texture.h"
#include "../BaseCode/Program.h"
#include "../Controllers/MovementController.h"
#include "../Controllers/CollisionController.h"

class Player {

public:
	
	
	Player(vec3 position, float radius);
	virtual ~Player();
	
	std::shared_ptr<Movement> movementComponent;
	std::shared_ptr<Transform> transformComponent;
	std::shared_ptr<Collision> collisionComponent;

};

#endif