#pragma once

#ifndef TRANSFORM_INCLUDED
#define TRANSFORM_INCLUDED

#include <glm\glm.hpp>

using namespace glm;
using namespace std;

class Transform {

public:

	Transform();
	Transform(vec3 position);
	Transform(vec3 position, vec3 rotation);
	Transform(vec3 position, vec3 rotation, vec3 scale);
	
	vec3 position;
	vec3 rotation;
	vec3 scale;

};

#endif