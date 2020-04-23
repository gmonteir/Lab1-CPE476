#include "Render.h"

Render::Render(shared_ptr<Shape> shape,
	shared_ptr<Program> program,
	shared_ptr<Texture> texture,
	shared_ptr<Transform> transform)
{
	Render::shape = shape;
	Render::program = program;
	Render::texture = texture;
	Render::transform = transform;
	Render::model = make_shared<MatrixStack>();
}

Render::~Render()
{
}

void Render::update()
{
	model->pushMatrix();
		model->translate(transform->position);
		model->rotate(transform->rotation.x, vec3(1, 0, 0));
		model->rotate(transform->rotation.y, vec3(0, 1, 0));
		model->rotate(transform->rotation.z, vec3(0, 0, 1));
		model->scale(transform->scale);
		texture->bind(program->getUniform("Texture0"));
		glUniformMatrix4fv(program->getUniform("M"), 1, GL_FALSE, value_ptr(model->topMatrix()));
		shape->draw(program);
		texture->unbind();
	model->popMatrix();
}
