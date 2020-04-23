#pragma once

#ifndef TRANSFORM_INCLUDED
#define TRANSFORM_INCLUDED

#include <glm\glm.hpp>
#include "Component.h"

using namespace glm;
using namespace std;

class Transform : public Component {

public:

	Transform();
	Transform(vec3 position);
	Transform(vec3 position, vec3 rotation);
	Transform(vec3 position, vec3 rotation, vec3 scale);
	void Transform::setPosition(vec3 position);
	void Transform::setRotation(vec3 rotation);
	void Transform::setScale(vec3 scale);
	void Transform::setRadius(float radius);
	
	vec3 position;
	vec3 rotation;
	vec3 scale;
	float radius;

};

#endif