#include "Textures.h"

Textures::Textures()
{
	if (instance == nullptr)
	{
		instance = make_shared<Textures>();
	}
}

Textures::~Textures()
{
	instance = nullptr;
}

void Textures::addTexture(const string& filename, const string& key)
{
	shared_ptr<Texture> temp = make_shared<Texture>();
	temp->setFilename(filename);
	temp->init();
	temp->setUnit(currentUnit);
	temp->setWrapModes(GL_REPEAT, GL_REPEAT);
	allTextures[key] = temp;
	currentUnit++;
}

shared_ptr<Texture> Textures::getTexture(const string& key)
{
	return allTextures[key];
}
