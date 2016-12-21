/*
Project - COMP371 - Summer 2016

The character.h is a child of the worldObject parent class and  it is where
- Create and draw functions for cars;
- Cars default attributes are set: Mass, Radius, Position and Velocity;

*/


#pragma once
#include "worldObject.h"
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

class character: public worldObject{


public:
	character(); 
	void drawHero(bool &survey_mode, float &y_rotation_angle, GLuint &modelVAO, GLuint &colorLoc, GLuint &transformLoc, std::vector<glm::vec3> &model_vertices, glm::vec3 player_position);
	void drawNormalCharacter(float &y_rotation_angle, GLuint &modelVAO, GLuint &colorLoc, GLuint &transformLoc, std::vector<glm::vec3> &model_vertices, glm::vec3 random_position, glm::vec3 bodyColor, glm::vec3 armColor);


private:
	//glm::vec3 player_position = glm::vec3(0.0f);
	glm::vec3 cube_scale = glm::vec3(0.10f);

};