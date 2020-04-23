#pragma once

#ifndef TEXTURES_INCLUDED
#define TEXTURES_INCLUDED

#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "../BaseCode/Texture.h"

using namespace std;

class Textures {

	static shared_ptr<Textures> instance;
	Textures() {};

public:

	static shared_ptr<Textures> getInstance();

	unordered_map<string, shared_ptr<Texture>> allTextures;
	int currentUnit = 0;
	void addTexture(const string& filename, const string& key);
	shared_ptr<Texture> getTexture(const string& key);
};

#endif