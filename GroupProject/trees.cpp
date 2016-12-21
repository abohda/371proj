#include "trees.h"

//Default constructor: 
tree::tree() {
	this->position = vec3(0.0f, 0.0f, 0.0f);
	this->mass = 1.0f;
	this->velocity = vec3(0.0f, 0.0f, 0.0f);
	radius = 0.5;
}

//Constructor: 
tree::tree(vec3 position, GLfloat m) : worldObject(position, m) {
	this->position = position;
	this->mass = m;
	this->velocity = vec3(0.0f, 0.0f, 0.0f);
};

//Vertices for the trunk and the leaves:
void tree::setVertices(float size) {

	this->vertices =
	{
		// triangle 1 
		vec3(-size, size, -size),
		vec3(-size,size, -size),
		vec3(size,-size, -size),
		// triangle 2 
		vec3(-size, size, -size),
		vec3(size, size, -size),
		vec3(size, -size, -size),

		// triangle 3
		vec3(size, size, size),
		vec3(size, -size, size),
		vec3(size, -size, -size),
		// triangle 4 
		vec3(size, size, size),
		vec3(size, size, -size),
		vec3(size, -size, -size),

		// triangle 3
		vec3(size,-size, size),
		vec3(-size,-size, size),
		vec3(-size, size, size),
		// triangle 4 
		vec3(size, -size, size),
		vec3(size, size, size),
		vec3(-size, size, size),

		// triangle 5 
		vec3(-size, -size, size),
		vec3(size, -size, size),
		vec3(size, -size, -size),
		// triangle 6  
		vec3(-size, -size, size),
		vec3(size, -size, -size),
		vec3(-size, -size, -size),

		// triangle 7 
		vec3(-size, size,-size),
		vec3(size, size, -size),
		vec3(-size, size, size),
		// triangle 8 
		vec3(-size, size, size),
		vec3(size, size, size),
		vec3(size, size, -size),

		// triangle 9 
		vec3(-size, size,-size),
		vec3(-size, -size, -size),
		vec3(-size, -size, size),
		//triangle 10
		vec3(-size, -size, size),
		vec3(-size, size,-size),
		vec3(-size, size, size),

		// triangle 11 
		vec3(size, size, -size),
		vec3(size, -size,-size),
		vec3(size, -size, size),
		// triangle 12  
		vec3(size, -size,-size),
		vec3(size, size, size),
		vec3(size, size, -size)
	};
}

//Set color for the trunk: 
void tree::setColor() {

	//Unique general colour for EACH points of each triangles:
	this->color = {

		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),

		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),

		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),

		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),

		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),

		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),

		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),

		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),

		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),

		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),

		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),

		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20),
		glm::vec3(0.36, 0.25, 0.20)
	};
}

//Set the color for the leaves: 
void tree::setColorLeaf() {

	this->color =
	{
		glm::vec3(0.0f, 0.771f, 0.0f),
		glm::vec3(0.0f, 0.115f, 0.0f),
		glm::vec3(0.0f, 0.483f, 0.0f),

		glm::vec3(0.0f, 0.771f, 0.0f),
		glm::vec3(0.0f, 0.115f, 0.0f),
		glm::vec3(0.0f, 0.483f, 0.0f),

		glm::vec3(0.0f, 0.771f, 0.0f),
		glm::vec3(0.0f, 0.115f, 0.0f),
		glm::vec3(0.0f, 0.483f, 0.0f),

		glm::vec3(0.0f, 0.771f, 0.0f),
		glm::vec3(0.0f, 0.115f, 0.0f),
		glm::vec3(0.0f, 0.483f, 0.0f),

		glm::vec3(0.0f, 0.115f, 0.0f),
		glm::vec3(0.0f, 0.483f, 0.0f),
		glm::vec3(0.0f, 0.771f, 0.0f),

		glm::vec3(0.0f, 0.115f, 0.0f),
		glm::vec3(0.0f, 0.483f, 0.0f),
		glm::vec3(0.0f, 0.771f, 0.0f),

		glm::vec3(0.0f, 0.771f, 0.0f),
		glm::vec3(0.0f, 0.115f, 0.0f),
		glm::vec3(0.0f, 0.483f, 0.0f),

		glm::vec3(0.0f, 0.771f, 0.0f),
		glm::vec3(0.0f, 0.483f, 0.0f),
		glm::vec3(0.0f, 0.115f, 0.0f),

		glm::vec3(0.0f, 0.115f, 0.0f),
		glm::vec3(0.0f, 0.483f, 0.0f),
		glm::vec3(0.0f, 0.771f, 0.0f),

		glm::vec3(0.0f, 0.771f, 0.0f),
		glm::vec3(0.0f, 0.483f, 0.0f),
		glm::vec3(0.0f, 0.115f, 0.0f),

		glm::vec3(0.0f, 0.771f, 0.0f),
		glm::vec3(0.0f, 0.115f, 0.0f),
		glm::vec3(0.0f, 0.483f, 0.0f),

		glm::vec3(0.0f, 0.483f, 0.0f),
		glm::vec3(0.0f, 0.771f, 0.0f),
		glm::vec3(0.0f, 0.115f, 0.0f)
	};

}

