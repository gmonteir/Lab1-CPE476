#pragma once

#ifndef RENDER_CONTROLLER_INCLUDED
#define RENDER_CONTROLLER_INCLUDED

#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "../Components/Render.h"

class RenderController {

public:

	RenderController();
	virtual ~RenderController();

	static std::shared_ptr<RenderController> instance;
	
	std::vector<Render> renderComponents;
	void update();

};

#endif