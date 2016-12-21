#include "worldObject.h"
#include "glm.hpp"
#include <math.h>

using namespace glm;

//Default constructor: 
worldObject::worldObject()
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->mass = 0.0;
}

//Constructor: 
worldObject::worldObject(glm::vec3 pos, GLfloat m)
{
	this->position = pos;
	this->mass = m;
}

//Return the mass of the object: 
double worldObject::getMass() { return this->mass; }
//Return the position of the object: 
glm::vec3 worldObject::getPosition() { return this->position; }
//Return the velocity of the object: 
glm::vec3 worldObject::getCurrentVelocity() { return this->velocity; }
//Return the color of the object: 
vector<glm::vec3> worldObject::getColor() { return this->color; }
//Return seperated coordinates positon of an object: 
GLfloat worldObject::getX() { return position.x; }
GLfloat worldObject::getY() { return position.y; }
GLfloat worldObject::getZ() { return position.z; }
//Return the radius of an object: 
GLfloat worldObject::getRadius() { return radius; }
//Return the vertices (if any) of an object: 
vector<vec3> worldObject::getVertices() { return this->vertices; }
 /*-------------------------------------------------------------------*/
//Set the position of the object: 
void worldObject::setPosition(glm::vec3 pos) { this->position = pos; }
//Set the current velocity of the object: 
void worldObject::setCurrentVelocity(glm::vec3 vel) {this->velocity = vel;}
//Set the mass of the object: 
void worldObject::setMass(GLfloat m) {this->mass = m;}


//Calculate the radius using the vertices of an object: 
//(Useful for a sphere, cubes and non-complex objects) 
void worldObject::calculateRadius()
{
	//Takes the furthest point inside the object: 
	GLfloat max_distance = 0.0f;
	GLfloat distance = 0.0f;

	for (vec3 p : vertices)
	{
		distance = sqrtf(pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2));

		if (distance >= max_distance) {
			max_distance = distance;
		}
	}

	radius = max_distance; 
	//radius = max_distance / 2.0f;
}
