#include "Shapes.h"

shared_ptr<Shapes> Shapes::getInstance()
{
	static shared_ptr<Shapes> instance(new Shapes);
	return instance;
}

void Shapes::addShape(const string& filename, const string& key)
{
	vector<tinyobj::shape_t> TOshapes;
	vector<tinyobj::material_t> objMaterials;
	string errStr;

	bool rc = tinyobj::LoadObj(TOshapes, objMaterials, errStr, (filename).c_str());
	if (!rc) {
		cerr << errStr << endl;
	}
	else {
		shared_ptr<Shape> temp = make_shared<Shape>();
		temp->createShape(TOshapes[0]);
		temp->measure();
		temp->init();
		allShapes[key] = temp;
	}
}

shared_ptr<Shape> Shapes::getShape(const string& key)
{
	return allShapes[key];
}
