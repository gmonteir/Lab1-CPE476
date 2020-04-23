#include "RenderController.h"

shared_ptr<RenderController> RenderController::getInstance()
{
	static shared_ptr<RenderController> instance(new RenderController);
	return instance;
}

void RenderController::update()
{
	for (size_t i = 0; i < renderComponents.size(); i++)
	{
		if (renderComponents[i] != nullptr) renderComponents[i]->update();
	}
}

void RenderController::addComponent(shared_ptr<Render>& render)
{
	renderComponents.push_back(render);
}
