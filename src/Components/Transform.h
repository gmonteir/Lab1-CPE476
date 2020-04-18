#pragma once

#ifndef TRANSFORM_INCLUDED
#define TRANSFORM_INCLUDED

#include <glm\glm.hpp>

using namespace glm;

class Transform {

public:

	vec3 position;
	vec3 rotation;
	vec3 scale;

};

#endif