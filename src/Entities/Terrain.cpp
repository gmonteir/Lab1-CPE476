#include "Terrain.h"
#include <iostream>
#include <cassert>

#include "../BaseCode/GLSL.h"
#include "../BaseCode/Program.h"


using namespace std;
using namespace glm;

Terrain::Terrain(vec3 position,
	shared_ptr<Shape> shape,
	shared_ptr<Program> program,
	shared_ptr<Texture> texture) {

	Terrain::transformComponent = make_shared<Transform>(position);
	//Terrain::collisionComponent = make_shared<Collision>(transformComponent, radius);
	Terrain::renderComponent = make_shared<Render>(transformComponent, shape, program, texture);

	TransformController::instance->addComponent(transformComponent);
	//CollisionController::instance->addComponent(collisionComponent);
	RenderController::instance->addComponent(renderComponent);
}

Terrain::~Terrain()
{
}