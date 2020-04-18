#include "Collectable.h"
#include <iostream>
#include <cassert>

#include "../BaseCode/GLSL.h"
#include "../BaseCode/Program.h"

using namespace std;
using namespace glm;

Collectable::Collectable() {
	Collectable::movementComponent = make_shared<Movement>();
	Collectable::positionComponent = make_shared<Position>();
	Collectable::collisionComponent = make_shared<Collision>();
	Collectable::renderComponent = make_shared<Render>();
}