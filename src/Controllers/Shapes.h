#pragma once

#ifndef SHAPES_INCLUDED
#define SHAPES_INCLUDED

#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <glm\glm.hpp>
#include "../BaseCode/Shape.h"

using namespace std;

class Shapes {

	static shared_ptr<Shapes> instance;
	Shapes() {};

public:

	static shared_ptr<Shapes> getInstance();

	unordered_map<string, shared_ptr<Shape>> allShapes;
	void addShape(const string& filename, const string& key);
	shared_ptr<Shape> getShape(const string& key);
};

#endif