#pragma once

#ifndef COLLECTABLE_RENDERER_INCLUDED
#define COLLECTABLE_RENDERER_INCLUDED

#include <glm\glm.hpp>
#include "Render.h"
#include "../BaseCode/Shape.h"
#include "../BaseCode/Texture.h"

using namespace std;
using namespace glm;

class CollectableRenderer : public Render {

public:

	CollectableRenderer(shared_ptr<MatrixStack> Projection,
		shared_ptr<MatrixStack> View,
		shared_ptr<Shape> shape, 
		shared_ptr<Program> program, 
		shared_ptr<Texture> texture);

	void update();

};

#endif