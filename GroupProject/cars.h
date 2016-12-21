/*
Project - COMP371 - Summer 2016

The cars.h  is a child of the worldObject parent class and  it is where
- Create and draw functions for cars; 
- Cars default attributes are set: Mass, Radius, Position and Velocity;

*/

#pragma once
//#include "objloader.hpp"
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

class cars : public worldObject {

public:
	cars(); 
	void createCars(std::vector<glm::vec3> car_vertices, std::vector<glm::vec3> car_normals, std::vector<glm::vec3> car_color);
	void drawCars(std::vector<glm::vec3> car_vertices, std::vector<glm::vec3> car_offsets, GLuint car_transformLoc);

private:

	GLuint carVAO;
	GLuint carVerticesVBO;
	GLuint carNormalsVBO;
	GLuint carColorVBO;

};