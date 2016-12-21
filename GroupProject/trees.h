/*
Project - COMP371 - Summer 2016

The trees.h  is a child of the worldObject parent class and  it is where
- Colors and vertices are set for the trunk and leaves of the tree; 
- Trees default attributes are set: Mass, Radius, Position and Velocity;

*/


#pragma once

#include <vector>
#include <glew.h>
#include <glfw3.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "worldObject.h"

class tree : public worldObject {

public:

	tree();
	tree(glm::vec3 position, GLfloat mass);
	void setVertices(float size);
	void setColor();
	void setColorLeaf();

private:
	GLuint UVs_VBO_tree, color_VBO1_tree, color_VBO2_tree, VBO_tree, VBO2_tree, VAO_tree, VAO2_tree;

};
