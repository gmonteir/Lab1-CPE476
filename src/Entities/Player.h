#pragma once

#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

class Player {

public:
	
	Player();
	virtual ~Player();
	
	Movement movementComponent;
	Position positionComponent;
	Collision collisionComponent;

};

#endif