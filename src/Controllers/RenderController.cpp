#include "RenderController.h"

RenderController::RenderController()
{
	if (instance == nullptr)
	{
		instance = make_shared<RenderController>();
	}
}

RenderController::~RenderController()
{
	if (instance)
	{
		instance = nullptr;
	}
}

void RenderController::update()
{
	for (size_t i = 0; i < renderComponents.size; i++)
	{
		renderComponents[i]->update();
	}
}

void RenderController::addComponent(shared_ptr<Render>& render)
{
	renderComponents.push_back(render);
}
