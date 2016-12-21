/*
Project - COMP371 - Summer 2016

The Building.h is where
- Procedural modelling of the buildings function are implemented; 
- Building default attributes are set: Mass, Radius, Position and Velocity; 
- The draw call is implemented

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
#include <stdlib.h>
#include <time.h>
#include "worldObject.h"

using namespace std;

class buildings : public worldObject{

public:
	buildings(GLuint buildingShaderProgram);
	void generateBuilding(GLfloat x, GLfloat z, GLfloat width, GLfloat height, GLfloat depth);
	void generateCity();
	void drawCity();
	vec3 getPosition(int i){
		return positions[i];
	}
	//void setColor();

private:
	vector<GLfloat> vertices;

	GLuint VAO, VBO;
	vector<GLuint> VAOs, VBOs;

	vector<GLfloat> UVs;
	GLuint UVs_VBO;

	vector<GLfloat> normals;
	GLuint normals_VBO;
	vector<glm::vec3> positions;
	vector<vector<GLfloat>> city;
	vector<glm::vec4> colours;
	GLuint building_colourLoc;

};