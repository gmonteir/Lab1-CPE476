#pragma once

#ifndef TERRAIN_INCLUDED
#define TERRAIN_INCLUDED

#include <memory>
#include "../Components/Movement.h"
#include "../Components/Transform.h"
#include "../Components/Collision.h"
#include "../Components/Render.h"
#include "../Controllers/MovementController.h"
#include "../Controllers/CollisionController.h"
#include "../Controllers/RenderController.h"

class Terrain {

public:

	Terrain(vec3 position, shared_ptr<Shape> shape, shared_ptr<Program> program, shared_ptr<Texture> texture);
	virtual ~Terrain();

	std::shared_ptr<Transform> transformComponent;
	//std::shared_ptr<Collision> collisionComponent;
	std::shared_ptr<Render> renderComponent;

};

#endif