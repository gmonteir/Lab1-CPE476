#pragma once

#ifndef RENDER_INCLUDED
#define RENDER_INCLUDED

#include <glm\glm.hpp>
#include "../BaseCode/Shape.h"
#include "../BaseCode/Texture.h"
#include "../BaseCode/Program.h"
#include "../BaseCode/MatrixStack.h"

using namespace std;
using namespace glm;

class Render {

public:

	virtual void update();

	shared_ptr<MatrixStack> Projection;
	shared_ptr<MatrixStack> View;
	shared_ptr<Shape> shape;
	shared_ptr<Program> program;
	shared_ptr<Texture> texture;

};

#endif