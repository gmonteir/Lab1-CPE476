#include "Transform.h"

Transform::Transform() {
	Transform::position = vec3(0, 0, 0);
	Transform::rotation = vec3(0, 0, 0);
	Transform::scale = vec3(1, 1, 1);
}

Transform::Transform(vec3 position) {
	Transform::position = position;
	Transform::rotation = vec3(0, 0, 0);
	Transform::scale = vec3(1, 1, 1);
}

Transform::Transform(vec3 position, vec3 rotation) {
	Transform::position = position;
	Transform::rotation = rotation;
	Transform::scale = vec3(1, 1, 1);
}

Transform::Transform(vec3 position, vec3 rotation, vec3 scale) {
	Transform::position = position;
	Transform::rotation = rotation;
	Transform::scale = scale;
}