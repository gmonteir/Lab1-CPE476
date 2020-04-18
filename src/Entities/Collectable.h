#pragma once

#ifndef COLLECTABLE_INCLUDED
#define COLLECTABLE_INCLUDED

class Collectable {

public:

	Collectable();
	virtual ~Collectable();
	
	Movement movementComponent;
	Position positionComponent;
	Collision collisionComponent;
	Render renderComponent;

};

#endif