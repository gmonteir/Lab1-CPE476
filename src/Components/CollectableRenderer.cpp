#include "CollectableRenderer.h"

CollectableRenderer::CollectableRenderer(shared_ptr<MatrixStack> Projection, 
	shared_ptr<MatrixStack> View, 
	shared_ptr<Shape> shape, 
	shared_ptr<Program> program, 
	shared_ptr<Texture> texture)
{
	CollectableRenderer::shape = shape;
	CollectableRenderer::program = program;
	CollectableRenderer::texture = texture;
}

void CollectableRenderer::update()
{
	program->bind();
	glUniformMatrix4fv(program->getUniform("P"), 1, GL_FALSE, value_ptr(Projection->topMatrix()));
	glUniformMatrix4fv(program->getUniform("V"), 1, GL_FALSE, value_ptr(lookAt(eye, center, up)));
	glUniform3f(program->getUniform("eyePos"), eye.x, eye.y, eye.z);

	// draw stuff
	Model->pushMatrix();
	Model->loadIdentity();

	// draw ground
	Model->pushMatrix();
	Model->scale(vec3(50, 1, 50));
	Model->translate(vec3(0, -1, 0));
	texture2->bind(program->getUniform("Texture0"));
	setModel(program, Model);
	terrain->draw(program);
	texture2->unbind();
	Model->popMatrix();
	program->unbind();
}
