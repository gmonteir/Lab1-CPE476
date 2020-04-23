#pragma once

#ifndef COLLECTABLE_INCLUDED
#define COLLECTABLE_INCLUDED

#include <memory>
#include "../Components/Movement.h"
#include "../Components/Transform.h"
#include "../Components/Collision.h"
#include "../Components/Render.h"
#include "../Controllers/MovementController.h"
#include "../Controllers/CollisionController.h"
#include "../Controllers/RenderController.h"

class Collectable {

public:

	Collectable(vec3 position, float radius, shared_ptr<Shape> shape, shared_ptr<Program> program, shared_ptr<Texture> texture);
	virtual ~Collectable();
	
	std::shared_ptr<Movement> movementComponent;
	std::shared_ptr<Transform> transformComponent;
	std::shared_ptr<Collision> collisionComponent;
	std::shared_ptr<Render> renderComponent;

	void setVelocity(vec3 velocity);
	void setRotateSpeed(vec3 rotateSpeed);
	void setScaleSpeed(vec3 scaleSpeed);

};

#endif