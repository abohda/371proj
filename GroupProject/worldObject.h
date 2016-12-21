/*
Project - COMP371 - Summer 2016

The wolrdObject.h is the base class of all objects in this application where
- Getters and setters for the position, colors, vertices, position and radius is implemented. 

*/


#pragma once
#include "..\glew\glew.h"
#include "glm.hpp"
#include <vector>

using namespace glm;
using namespace std;

class worldObject
{

public:

	worldObject();
	worldObject(glm::vec3 pos, GLfloat m);



	void setMass(GLfloat m);
	double getMass();
	vector<vec3> getVertices();
	vector<vec3> getColor();

	glm::vec3 getCurrentVelocity();
	void setCurrentVelocity(glm::vec3 vel);

	glm::vec3 getPosition();
	void setPosition(glm::vec3 pos);
	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();

	GLfloat getRadius();
	void calculateRadius();

protected:

	double mass;
	glm::vec3 position;
	glm::vec3 velocity;
	vector<glm::vec3> vertices;
	vector<glm::vec3> color;
	GLfloat radius;

};