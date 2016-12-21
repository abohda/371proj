/*
Project - COMP371 - Summer 2016

The collisions.h is where
- Detect collision: isCollide by using the radius and position of two world objects; 
- The isCollide function is called inside the doCollisions where if there is a collision, the collision response occurs. 

*/
#pragma once
#include "worldObject.h"

class collisions
{

public:
	void doCollisions(float radius1, float mass1, vec3 position1, vec3& velocity1, float radius2, float mass2, vec3 position2, vec3& velocity2, string type);
	bool isCollide(float radius1, vec3 position1, float radius2, vec3 position2);
};
