#include "Movement.h"

Movement::Movement(shared_ptr<Transform> transform) {
	Movement::transform = transform;
	Movement::velocity = vec3(0, 0, 0);
	Movement::rotateSpeed = vec3(0, 0, 0);
	Movement::scaleSpeed = vec3(0, 0, 0);
}

Movement::Movement(shared_ptr<Transform> transform, vec3 velocity) {
	Movement::transform = transform;
	Movement::velocity = velocity;
	Movement::rotateSpeed = vec3(0, 0, 0);
	Movement::scaleSpeed = vec3(0, 0, 0);
	
}

Movement::Movement(shared_ptr<Transform> transform, vec3 velocity, vec3 rotateSpeed) {
	Movement::transform = transform;
	Movement::velocity = velocity;
	Movement::rotateSpeed = rotateSpeed;
	Movement::scaleSpeed = vec3(0, 0, 0);
}

Movement::Movement(shared_ptr<Transform> transform, vec3 velocity, vec3 rotateSpeed, vec3 scaleSpeed) {
	Movement::transform = transform;
	Movement::velocity = velocity;
	Movement::rotateSpeed = rotateSpeed;
	Movement::scaleSpeed = scaleSpeed;
}

Movement::~Movement() {

}

void Movement::update() {
	Movement::transform->position += Movement::velocity;
	Movement::transform->rotation += Movement::rotateSpeed;
	Movement::transform->scale += Movement::scaleSpeed;
}

void Movement::setVelocity(vec3 velocity) {
	Movement::velocity = velocity;
}

void Movement::setRotateSpeed(vec3 rotateSpeed) {
	Movement::rotateSpeed = rotateSpeed;
}

void Movement::setScaleSpeed(vec3 scaleSpeed) {
	Movement::scaleSpeed = scaleSpeed;
}
