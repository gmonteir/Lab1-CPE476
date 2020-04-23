#include "Collectable.h"
#include <iostream>
#include <cassert>

#include "../BaseCode/GLSL.h"
#include "../BaseCode/Program.h"

using namespace std;
using namespace glm;

Collectable::Collectable(vec3 position, 
	float radius,
	shared_ptr<Shape> shape, 
	shared_ptr<Program> program, 
	shared_ptr<Texture> texture) {

	Collectable::transformComponent = make_shared<Transform>(position);
	Collectable::movementComponent = make_shared<Movement>(transformComponent);
	Collectable::collisionComponent = make_shared<Collision>(transformComponent, radius);
	Collectable::renderComponent = make_shared<Render>(shape, program, texture, transformComponent);

	TransformController::getInstance()->addComponent(transformComponent);
	MovementController::getInstance()->addComponent(movementComponent);
	CollisionController::getInstance()->addComponent(collisionComponent);
	RenderController::getInstance()->addComponent(renderComponent);
}

Collectable::~Collectable()
{
}

void Collectable::setVelocity(vec3 velocity) {
	movementComponent->setVelocity(velocity);
}

void Collectable::setRotateSpeed(vec3 rotateSpeed) {
	movementComponent->setRotateSpeed(rotateSpeed);
}

void Collectable::setScaleSpeed(vec3 scaleSpeed) {
	movementComponent->setScaleSpeed(scaleSpeed);
}