#include "Movement.h"

using namespace std;

#include "../BaseCode/GLSL.h"
#include "../BaseCode/Program.h"

Movement::Movement(shared_ptr<Transform> transform) {
	Movement::transform = transform;
	Movement::velocity = vec3(0, 0, 0);
}

Movement::Movement(shared_ptr<Transform> transform, vec3 velocity) {
	Movement::transform = transform;
	Movement::velocity = velocity;
}

Movement::~Movement() {

}

void Movement::update() {
	Movement::transform->position = Movement::transform->position + Movement::velocity;
}

void Movement::setVelocity(vec3 velocity) {
	Movement::velocity = velocity;
}
