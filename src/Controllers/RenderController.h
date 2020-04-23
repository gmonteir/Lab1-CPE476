#pragma once

#ifndef RENDER_CONTROLLER_INCLUDED
#define RENDER_CONTROLLER_INCLUDED

#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "../Components/Render.h"

class RenderController {

	static std::shared_ptr<RenderController> instance;
	RenderController() {};

public:

	static shared_ptr<RenderController> getInstance();
	
	std::vector<shared_ptr<Render>> renderComponents;
	void update();
	void RenderController::addComponent(shared_ptr<Render>& render);

};

#endif