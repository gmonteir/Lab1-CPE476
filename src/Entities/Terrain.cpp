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
	Terrain::renderComponent = make_shared<Render>(shape, program, texture, transformComponent);

	/*Terrain::transformComponent->parent = (GameObject*)(this);
	Terrain::renderComponent->parent = (GameObject*)(this);*/

	TransformController::getInstance()->addComponent(transformComponent);
	//CollisionController::instance->addComponent(collisionComponent);
	RenderController::getInstance()->addComponent(renderComponent);
}

Terrain::~Terrain()
{
}