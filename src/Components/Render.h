#pragma once

#ifndef RENDER_INCLUDED
#define RENDER_INCLUDED

#include <glm\glm.hpp>
#include "../BaseCode/Shape.h"
#include "../BaseCode/Texture.h"
#include "../BaseCode/Program.h"
#include "../BaseCode/MatrixStack.h"
#include "Component.h"
#include "Transform.h"

using namespace std;
using namespace glm;

class Render : public Component {

public:

	shared_ptr<Shape> shape;
	shared_ptr<Program> program;
	shared_ptr<Texture> texture;
	shared_ptr<Transform> transform;
	shared_ptr<MatrixStack> model;
	
	Render(shared_ptr<Shape> shape,
		shared_ptr<Program> program,
		shared_ptr<Texture> texture,
		shared_ptr<Transform> transform);

	virtual ~Render();
	
	void update();

};

#endif