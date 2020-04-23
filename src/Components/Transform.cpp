#include "Transform.h"

Transform::Transform() {
	Transform::position = vec3(0, 0, 0);
	Transform::rotation = vec3(0, 0, 0);
	Transform::scale = vec3(1, 1, 1);
	Transform::radius = 0.0;
}

Transform::Transform(vec3 position) {
	Transform::position = position;
	Transform::rotation = vec3(0, 0, 0);
	Transform::scale = vec3(1, 1, 1);
	Transform::radius = 0.0;
}

Transform::Transform(vec3 position, vec3 rotation) {
	Transform::position = position;
	Transform::rotation = rotation;
	Transform::scale = vec3(1, 1, 1);
	Transform::radius = 0.0;
}

Transform::Transform(vec3 position, vec3 rotation, vec3 scale) {
	Transform::position = position;
	Transform::rotation = rotation;
	Transform::scale = scale;
	Transform::radius = 0.0;
}

void Transform::setPosition(vec3 position) {
	Transform::position = position;
}

void Transform::setRotation(vec3 rotation) {
	Transform::rotation = rotation;
}

void Transform::setScale(vec3 scale) {
	Transform::scale = scale;
}

void Transform::setRadius(float radius) {
	Transform::radius = radius;
}