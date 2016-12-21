/*
Project - COMP371 - Summer 2016

The main.cpp is where 
- All objects are initialized and drawn; 
- Callbacks functions and event modes are seperate functions;  
- The Opengl environment is initialized and linked with the shaders; 
- The game loop occurs. 

*/


//Group Project
#include "stdafx.h"
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
#include <../GroupProject/objloader.hpp>
#include <../soil/SOIL.h>
//Wold Objects: 
#include "Buildings.h"
#include "cars.h" 
#include "character.h"
#include "trees.h"
#include "collisions.h"

using namespace std;

// Window dimensions
const GLuint WINDOW_WIDTH = 1000, WINDOW_HEIGHT = 1000;
//Main character's movements: 
const float PLAYER_POSITION_STEP = 0.1f;
const float PLAYER_Y_POSITION_STEP = 2.0f;
const float ANGLE_ROTATION_STEP = 0.15f;
const float SURVEY_TARGET_MOVE_STEP_Y = 1.0f;
const float PI = 3.1415927;
const float groundSize = 60.0f;

//Main character's attributes: 
glm::vec3 player_previous_position = glm::vec3(0.0f);
glm::vec3 player_velocity = glm::vec3(0.0f);
glm::vec3 player_position = glm::vec3(0.0f);
glm::vec3 survey_camera_target = glm::vec3(0.0f);
float survey_target_change = 0.0f;

//default number of objects: 
const int numberOfTrees = 35;
const int numberOfCharacters = 30;
const int numberOfCarInstances = 40;

//View and Projection initialization: 
glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, -15.0f);
glm::mat4 projection_matrix;

//Boolean variables: 
bool move_player_forward = false;
bool move_player_backward = false;
bool teleportation_mode = false;
bool survey_mode = false;

//For uniform variable passed to GLSL: 
GLuint projectionLoc;
GLuint viewMatrixLoc;
GLuint transformLoc;
GLuint colorLoc; // used for object color
GLuint viewPosLoc; // used for specular lighting 

GLuint teleportation_transformLoc;
GLuint teleportation_colorLoc;
GLuint teleportation_viewPosLoc; 

GLuint car_projectionLoc;
GLuint car_viewMatrixLoc;
GLuint car_transformLoc;
GLint car_viewPosLoc;

GLuint tree_projectionLoc;
GLuint tree_viewMatrixLoc;
GLuint tree_transformLoc;
GLuint treeShaderProgram;

//GLuint car_altColorLoc;

GLuint ground_projectionLoc;
GLuint ground_viewMatrixLoc;
GLuint ground_transformLoc;
GLint ground_viewPosLoc;


GLuint building_transformLoc;
GLuint building_viewMatrixLoc;
GLuint building_projectionLoc;
GLuint building_colourLoc;
GLuint building_viewPosLoc;

//Vertices to load a cube obj file: 
std::vector<glm::vec3> model_vertices;

//2D vector of type GLfloat the procedural modelling of the buildings: 
vector<vector<GLfloat>> city;
vector<GLfloat> UVs; // UV coordinates for texture
vector<GLfloat> normals; // normals of an object 
vector<tree> leaf, trunk; // holds tree objects

//VAOs & VBOs: 
GLuint modelVAO;
GLuint VAO, VBO;
vector<GLuint> VAOs, VBOs;
GLuint UVs_VBO;
GLuint normals_VBO;
GLuint UVs_VBO_tree, color_VBO1_tree, color_VBO2_tree, VBO_tree, VBO2_tree, VAO_tree, VAO2_tree;

float y_rotation_angle = 0.0f; // of the model

/*Initialize a tree object: */
void createTree(tree& tronc, tree& leaf) {
	tronc.setVertices(0.3f);
	tronc.setColor();

	leaf.setVertices(0.4f);
	leaf.setColorLeaf();

	//calculate objects' radius: 
	//tronc.calculateRadius();
	leaf.calculateRadius();

	//for texture (U/V coordinates)
	vector<GLfloat> UVs;

	//trunck texture: 
	UVs = {
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,


		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f
	};

	//tronc: 
	glGenVertexArrays(1, &VAO_tree);
	glBindVertexArray(VAO_tree);
	// Bind the vertices buffer to the VAO: 
	glGenBuffers(1, &VBO_tree);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_tree);
	glBufferData(GL_ARRAY_BUFFER, tronc.getVertices().size() * sizeof(glm::vec3), &tronc.getVertices()[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	// Bind the color buffer to the VAO: 
	glGenBuffers(1, &color_VBO1_tree);
	glBindBuffer(GL_ARRAY_BUFFER, color_VBO1_tree);
	glBufferData(GL_ARRAY_BUFFER, tronc.getColor().size() * sizeof(glm::vec3), &tronc.getColor()[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, color_VBO1_tree);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glGenBuffers(1, &UVs_VBO_tree);
	glBindBuffer(GL_ARRAY_BUFFER, UVs_VBO_tree);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindVertexArray(0); // Unbind ground VAO

	//leaves: 
	glGenVertexArrays(1, &VAO2_tree);
	glBindVertexArray(VAO2_tree);
	// Bind the vertices buffer to the VAO: 
	glGenBuffers(1, &VBO2_tree);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2_tree);
	glBufferData(GL_ARRAY_BUFFER, leaf.getVertices().size() * sizeof(glm::vec3), &leaf.getVertices()[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	// Bind the color buffer to the VAO: 
	glGenBuffers(1, &color_VBO2_tree);
	glBindBuffer(GL_ARRAY_BUFFER, color_VBO2_tree);
	glBufferData(GL_ARRAY_BUFFER, leaf.getColor().size() * sizeof(glm::vec3), &leaf.getColor()[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, color_VBO2_tree);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0); // Unbind ground VAO
}
/*Function called to draw the tree obejct: base->trunk and top->leaves */
void drawTree(tree& tronc, tree& leaf, glm::vec3 random_position) {

	glm::mat4 tree_model_matrix = glm::mat4(1.0f);

	// Cube controls
	tree_model_matrix = glm::mat4(1.0f);
	tree_model_matrix = glm::translate(tree_model_matrix, random_position);
	tree_model_matrix = glm::scale(tree_model_matrix, glm::vec3(0.5f, 2.5f, 0.5f));
	tree_model_matrix = glm::rotate(tree_model_matrix, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	tree_model_matrix = scale(tree_model_matrix, glm::vec3(1.2f, 6.0f, 1.2f));

	glUniformMatrix4fv(tree_transformLoc, 1, GL_FALSE, glm::value_ptr(tree_model_matrix));

	// Draw tronc
	glBindVertexArray(VAO_tree);
	glDrawArrays(GL_TRIANGLES, 0, tronc.getVertices().size());
	glBindVertexArray(0);

	// Cube controls
	tree_model_matrix = glm::mat4(1.0f);
	tree_model_matrix = glm::translate(tree_model_matrix, random_position);
	tree_model_matrix = glm::scale(tree_model_matrix, glm::vec3(2.0f, 1.5f, 2.0f));
	tree_model_matrix = glm::translate(tree_model_matrix, glm::vec3(0.0f, 3.0f, 0.0f));

	glUniformMatrix4fv(tree_transformLoc, 1, GL_FALSE, glm::value_ptr(tree_model_matrix));

	// Draw Big leaf
	glBindVertexArray(VAO2_tree);
	glDrawArrays(GL_TRIANGLES, 0, leaf.getVertices().size());
	glBindVertexArray(0);

	// Cube controls 1
	tree_model_matrix = glm::mat4(1.0f);
	tree_model_matrix = glm::translate(tree_model_matrix, random_position);
	tree_model_matrix = glm::scale(tree_model_matrix, glm::vec3(2.0f, 1.5f, 2.0f));
	tree_model_matrix = glm::translate(tree_model_matrix, glm::vec3(0.0f, 1.5f, 0.0f));

	glUniformMatrix4fv(tree_transformLoc, 1, GL_FALSE, glm::value_ptr(tree_model_matrix));

	// Draw Big leaf 2
	glBindVertexArray(VAO2_tree);
	glDrawArrays(GL_TRIANGLES, 0, leaf.getVertices().size());
	glBindVertexArray(0);

	// Cube controls
	tree_model_matrix = glm::mat4(1.0f);
	tree_model_matrix = glm::translate(tree_model_matrix, random_position);
	tree_model_matrix = glm::scale(tree_model_matrix, glm::vec3(3.0f, 3.0f, 3.0f));
	tree_model_matrix = glm::translate(tree_model_matrix, glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(tree_transformLoc, 1, GL_FALSE, glm::value_ptr(tree_model_matrix));

	// Draw Big leaf 3
	glBindVertexArray(VAO2_tree);
	glDrawArrays(GL_TRIANGLES, 0, leaf.getVertices().size());
	glBindVertexArray(0);

	// Cube controls
	tree_model_matrix = glm::mat4(1.0f);
	tree_model_matrix = glm::translate(tree_model_matrix, random_position);
	tree_model_matrix = scale(tree_model_matrix, glm::vec3(0.2f, 0.2f, 0.2f));
	tree_model_matrix = glm::rotate(tree_model_matrix, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	tree_model_matrix = glm::translate(tree_model_matrix, glm::vec3(1.0f, 3.5f, -2.0f));

	glUniformMatrix4fv(tree_transformLoc, 1, GL_FALSE, glm::value_ptr(tree_model_matrix));

	// Draw small leaf 1
	glBindVertexArray(VAO2_tree);
	glDrawArrays(GL_TRIANGLES, 0, leaf.getVertices().size());
	glBindVertexArray(0);

	tree_model_matrix = glm::mat4(1.0f);
	tree_model_matrix = glm::translate(tree_model_matrix, random_position);
	tree_model_matrix = scale(tree_model_matrix, glm::vec3(0.27f, 0.27f, 0.27f));
	tree_model_matrix = glm::translate(tree_model_matrix, glm::vec3(0.8f, 4.5f, -1.4f));

	glUniformMatrix4fv(tree_transformLoc, 1, GL_FALSE, glm::value_ptr(tree_model_matrix));

	// Draw small leaf 2
	glBindVertexArray(VAO2_tree);
	glDrawArrays(GL_TRIANGLES, 0, leaf.getVertices().size());
	glBindVertexArray(0);

	tree_model_matrix = glm::mat4(1.0f);
	tree_model_matrix = glm::translate(tree_model_matrix, random_position);
	tree_model_matrix = scale(tree_model_matrix, glm::vec3(0.2f, 0.2f, 0.2f));
	tree_model_matrix = glm::rotate(tree_model_matrix, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	tree_model_matrix = glm::translate(tree_model_matrix, glm::vec3(1.1f, 6.6f, 0.0f));

	glUniformMatrix4fv(tree_transformLoc, 1, GL_FALSE, glm::value_ptr(tree_model_matrix));

	// Draw small leaf 3
	glBindVertexArray(VAO2_tree);
	glDrawArrays(GL_TRIANGLES, 0, leaf.getVertices().size());
	glBindVertexArray(0);

	tree_model_matrix = glm::mat4(1.0f);
	tree_model_matrix = glm::translate(tree_model_matrix, random_position);
	tree_model_matrix = scale(tree_model_matrix, glm::vec3(0.2f, 0.2f, 0.2f));
	tree_model_matrix = glm::rotate(tree_model_matrix, 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	tree_model_matrix = glm::translate(tree_model_matrix, glm::vec3(-0.5f, 6.6f, -1.0f));

	glUniformMatrix4fv(tree_transformLoc, 1, GL_FALSE, glm::value_ptr(tree_model_matrix));

	// Draw small leaf 3
	glBindVertexArray(VAO2_tree);
	glDrawArrays(GL_TRIANGLES, 0, leaf.getVertices().size());
	glBindVertexArray(0);


}
/*Creates many tree objects by calling the two functions above*/
void createManyTrees(){
	for (int i = 0; i < numberOfTrees; i++){
		tree t = tree();
		tree l = tree();
		createTree(t,l);
		trunk.push_back(t);
		leaf.push_back(l);
	}
}
/*Special feature of the game: the user can enter a 'map' mode where he or she can teleport the main character anywhere in the world*/
void teleport(GLFWwindow* window){
	
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	height = height / 2;
	width = width / 2;

	x = (x - width) / width;
	y = -(y - height) / height;

	if (x > 0.9 || x < -0.9 || y > 0.9 || y < -0.9){
		cout << "coordinates out of bound" << endl;
	}
	else{
		teleportation_mode = false;
		player_position.x = x * -1.0f * groundSize;
		player_position.y = 18.0f;
		player_position.z = y * groundSize;
	}
}
/*Update the Projection matrix after a window resize event*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	projection_matrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 2000.0f); 
}
/*Mouse callback function*/
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//LEFT MOUSE -> Make main character move forward
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
		if (!teleportation_mode){
			if (!survey_mode)
				move_player_forward = true;
		}
		else
			teleport(window);
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
		move_player_forward = false;
	//RIGHT MOUSE -> Make main character move backward 
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
		if (!survey_mode)
			move_player_backward = true;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
		move_player_backward = false;
}
/*Keyboard callback function*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	//Exit the window and application: 
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (!survey_mode){
		if (key == GLFW_KEY_DOWN && action == GLFW_PRESS){
			player_previous_position.y = player_position.y;
			
			if (player_position.y - PLAYER_Y_POSITION_STEP >= 0.0f)
				player_position.y -= PLAYER_Y_POSITION_STEP;
			else
				player_position.y = 0.0f;
		}
		//Fly:
		if (key == GLFW_KEY_UP && action == GLFW_PRESS){
			player_previous_position.y = player_position.y;
			if (player_position.y + PLAYER_Y_POSITION_STEP <= 20.0f)
				player_position.y += PLAYER_Y_POSITION_STEP;
			else
				player_position.y = 20.0f;
		}
		//Rotate camera: 
		if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
			y_rotation_angle -= ANGLE_ROTATION_STEP;

		if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
			y_rotation_angle += ANGLE_ROTATION_STEP;
	}
	//Teleportation mode: 
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
		if (!teleportation_mode)
			teleportation_mode = true;
		else
			teleportation_mode = false;
	if (!teleportation_mode){
		if (key == GLFW_KEY_C && action == GLFW_PRESS)
			if (!survey_mode)
				survey_mode = true;
			else{
				survey_mode = false;
				survey_target_change = 0.0f;
			}
	}
	if (survey_mode){
		if (key == GLFW_KEY_W && action == GLFW_PRESS)
			if (survey_target_change + SURVEY_TARGET_MOVE_STEP_Y < 10.5f)
				survey_target_change += SURVEY_TARGET_MOVE_STEP_Y;
		if (key == GLFW_KEY_S && action == GLFW_PRESS)
			if (survey_target_change - SURVEY_TARGET_MOVE_STEP_Y > -2.5f)
				survey_target_change -= SURVEY_TARGET_MOVE_STEP_Y;
		if (key == GLFW_KEY_D && action == GLFW_PRESS)
			y_rotation_angle -= ANGLE_ROTATION_STEP;

		if (key == GLFW_KEY_A && action == GLFW_PRESS)
			y_rotation_angle += ANGLE_ROTATION_STEP;
	}
	
}

/*Load shaders*/
GLuint loadShaders(std::string vertex_shader_path, std::string fragment_shader_path) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_shader_path, std::ios::in);

	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ?\n", vertex_shader_path.c_str());
		getchar();
		exit(-1);
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_shader_path, std::ios::in);

	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ?\n", fragment_shader_path.c_str());
		getchar();
		exit(-1);
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s", vertex_shader_path.c_str());
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_shader_path.c_str());
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);

	glBindAttribLocation(ProgramID, 0, "in_Position");

	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID); //free up memory
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}
/*Load cubemap*/
GLuint loadCubemap(vector<const GLchar*> faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
			);

		SOIL_free_image_data(image); //free resources
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}

/*Update the main characters movement in the world*/
void movePlayer(GLFWwindow* window){
	double mY, mX;

	glfwGetCursorPos(window, &mX, &mY);

	player_previous_position.x = player_position.x;
	player_previous_position.z = player_position.z;

	if (move_player_forward == true){
		if (player_position.z + PLAYER_POSITION_STEP*cos(y_rotation_angle) <= groundSize && player_position.z + PLAYER_POSITION_STEP*cos(y_rotation_angle) >= -1 * groundSize)
			player_position.z += PLAYER_POSITION_STEP*cos(y_rotation_angle);
		else
			if (player_position.z > 0)
				player_position.z = groundSize;
			else
				player_position.z = -1 * groundSize;
		if (player_position.x + PLAYER_POSITION_STEP*sin(y_rotation_angle) <= groundSize && player_position.x + PLAYER_POSITION_STEP*sin(y_rotation_angle) >= -1 * groundSize)
			player_position.x += PLAYER_POSITION_STEP*sin(y_rotation_angle);
		else
			if (player_position.x > 0)
				player_position.x = groundSize;
			else
				player_position.x = -1 * groundSize;
	}
	if (move_player_backward == true){
		if (player_position.z - PLAYER_POSITION_STEP*cos(y_rotation_angle) <= groundSize && player_position.z - PLAYER_POSITION_STEP*cos(y_rotation_angle) >= -1 * groundSize)
			player_position.z -= PLAYER_POSITION_STEP*cos(y_rotation_angle);
		else
			if (player_position.z > 0)
				player_position.z = groundSize;
			else
				player_position.z = -1 * groundSize;
		if (player_position.x - PLAYER_POSITION_STEP*sin(y_rotation_angle) <= groundSize && player_position.x - PLAYER_POSITION_STEP*sin(y_rotation_angle) >= -1 * groundSize)
			player_position.x -= PLAYER_POSITION_STEP*sin(y_rotation_angle);
		else
			if (player_position.x > 0)
				player_position.x = groundSize;
			else
				player_position.x = -1 * groundSize;
	}

	player_velocity = player_position - player_previous_position;
	
}

int main()
{
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "City Stroll", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// Set the required callback functions
	glfwSetKeyCallback(window, key_callback);
	//Set mouse callback
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	//buffer_size callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	/*Link with shaders*/
	GLuint cubeShaderProgram = loadShaders("shaders/cube_vertex.shader", "shaders/cube_fragment.shader");
	GLuint skyboxShaderProgram = loadShaders("shaders/skybox_vertex.shader", "shaders/skybox_fragment.shader");
	GLuint teleportationShaderProgram = loadShaders("shaders/teleportation_vertex.shader", "shaders/teleportation_fragment.shader");
	GLuint carShaderProgram = loadShaders("shaders/car_vertex.shader", "shaders/car_fragment.shader");
	GLuint groundShaderProgram = loadShaders("shaders/ground_vertex.shader", "shaders/ground_fragment.shader");
	GLuint buildingShaderProgram = loadShaders("shaders/building_vertex.shader", "shaders/building_fragment.shader");
	GLuint treeShaderProgram = loadShaders("shaders/tree_vertex.shader", "shaders/tree_fragment.shader");

	/*Perspective projection matrix*/
	projection_matrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	
	/*Initialize and bind the cube's attributes*/
	std::vector<glm::vec3> model_normals;
	std::vector<glm::vec2> model_UVs;

	loadOBJ("cube.obj", model_vertices, model_normals, model_UVs);

	//prepare model VAO
	GLuint modelVerticesVBO, modelNormalsVBO, modelUVsVBO;

	glGenVertexArrays(1, &modelVAO);
	glBindVertexArray(modelVAO);

	glGenBuffers(1, &modelVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, modelVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, model_vertices.size() * sizeof(glm::vec3), &model_vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &modelNormalsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, modelNormalsVBO);
	glBufferData(GL_ARRAY_BUFFER, model_normals.size() * sizeof(glm::vec3), &model_normals.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindVertexArray(0);
	
	/*Initialize and bind the sky-box attributes*/
	std::vector<glm::vec3> skybox_vertices;
	std::vector<glm::vec3> skybox_normals; //unused
	std::vector<glm::vec2> skybox_UVs; //unused

	loadOBJ("cube.obj", skybox_vertices, skybox_normals, skybox_UVs);

	//prepare skybox VAO
	GLuint skyboxVAO, skyboxVerticesVBO;

	glGenVertexArrays(1, &skyboxVAO);
	glBindVertexArray(skyboxVAO);

	glGenBuffers(1, &skyboxVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, skybox_vertices.size() * sizeof(glm::vec3), &skybox_vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);	
	
	//prepare skybox cubemap
	vector<const GLchar*> faces;
	faces.push_back("images/posx.jpg");
	faces.push_back("images/negx.jpg");
	faces.push_back("images/posy.jpg");
	faces.push_back("images/negy.jpg");
	faces.push_back("images/posz.jpg");
	faces.push_back("images/negz.jpg");

	glActiveTexture(GL_TEXTURE1);
	GLuint cubemapTexture = loadCubemap(faces);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);

	/*Initialize the car attributes:*/
	std::vector<glm::vec3> car_vertices;
	std::vector<glm::vec3> car_normals; 
	std::vector<glm::vec3> car_color; 

	std::vector<glm::vec3> car_offsets;
	std::vector<glm::vec3> caracter_offsets;
	std::vector<glm::vec3> tree_offsets; 
	std::vector<glm::vec3> color_offsets;
	std::vector<glm::vec3> color2_offsets;

	srand(time(NULL));

	/*The following for-loops assign random position for the cars, normal characters and trees using a random number generator*/
	for (int i = 0; i < numberOfCarInstances; i++){
		
		glm::vec3 newOffset;		
		
		newOffset.x = (float)(rand() % 1000) / 1000.0f;
		newOffset.y = 0.0f; //(float)(rand() % 1000) / 1000.0f;
		newOffset.z = (float)(rand() % 1000) / 1000.0f;
		
		car_offsets.push_back(newOffset);
	}

	for (int i = 0; i < numberOfCharacters; i++){

		glm::vec3 newOffset;

		newOffset.x = (float)(rand() % 1000) / 1000.0f;
		newOffset.y = (float)(rand() % 1000) / 1000.0f;
		newOffset.z = (float)(rand() % 1000) / 1000.0f;

		color_offsets.push_back(newOffset);

		newOffset.x = (float)(rand() % 1000) / 1000.0f;
		newOffset.y = (float)(rand() % 1000) / 1000.0f;
		newOffset.z = (float)(rand() % 1000) / 1000.0f;

		color2_offsets.push_back(newOffset);

		newOffset.x = (float)(rand() % 1000) / 1000.0f;
		newOffset.y = 0.0f; //(float)(rand() % 1000) / 1000.0f;
		newOffset.z = (float)(rand() % 1000) / 1000.0f;

		caracter_offsets.push_back(newOffset);
	}
	
	for (int i = 0; i < numberOfTrees; i++) {
		glm::vec3 newOffset;

		newOffset.x = (float)(rand() % 1000) / 1000.0f;
		newOffset.y = 0.0f; //(float)(rand() % 1000) / 1000.0f;
		newOffset.z = (float)(rand() % 1000) / 1000.0f;

		tree_offsets.push_back(newOffset);
	}
	 
	//Initializ the cars from the game objects: 
	cars gamecars = cars();

	loadOBJ2("car.obj", car_vertices,car_normals,car_color);
	
	gamecars.createCars(car_vertices, car_normals, car_color);
	
	/*The teleportation screen map*/
	std::vector<GLfloat> tele_screen_vertices;
	std::vector<GLuint> tele_screen_indices;

	tele_screen_vertices = {
		-0.9f, 0.9f, 0.01f,
		-0.9f, -0.9f, 0.01f,
		0.9f, -0.9f, 0.01f,
		0.9f, 0.9f, 0.01f
	};

	tele_screen_indices = {
		0, 1, 2,
		0, 2, 3
	};


	GLfloat point[] = { 0.0f, 0.0f, 0.0f };

	GLuint VAO2, VBO2, EBO2, VAO3, VBO3;

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2); //index buffer

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, tele_screen_vertices.size() * sizeof(GLfloat), &tele_screen_vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//bind the element array buffer (containing indices to vertices in the array buffer)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, tele_screen_indices.size() * sizeof(GLuint), &tele_screen_indices.front(), GL_STATIC_DRAW); //populate the element array buffer

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0);

	glGenVertexArrays(1, &VAO3);
	glGenBuffers(1, &VBO3);

	glBindVertexArray(VAO3);

	glBindBuffer(GL_ARRAY_BUFFER, VBO3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point)* sizeof(GLfloat), point, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs), remember: do NOT unbind the EBO, keep it bound to this VAO

	/*The floor's dimension, color and texture*/
	GLfloat ground_Vertices[] = {
		// Positions          
		groundSize, -0.31f, groundSize,
		-1 * groundSize, -0.31f, groundSize,
		-1 * groundSize, -0.31f, -1 * groundSize,
		groundSize, -0.31f, groundSize,
		-1 * groundSize, -0.31f, -1 * groundSize,
		groundSize, -0.31f, -1 * groundSize
	};

	GLfloat ground_Color[] = {
		0.50f, 0.30f, 0.30f,
		0.50f, 0.30f, 0.30f,
		0.50f, 0.30f, 0.30f,
		0.50f, 0.30f, 0.30f,
		0.50f, 0.30f, 0.30f,
		0.50f, 0.30f, 0.30f
	};

	GLfloat ground_UVs[] = {
		0.0f, 1.0f,
		0.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		0.0f, 1.0f
	};

	//setup model texture
	
	glActiveTexture(GL_TEXTURE2); //select texture unit 2

	GLuint ground_texture;
	glGenTextures(1, &ground_texture);
	glBindTexture(GL_TEXTURE_2D, ground_texture); //bind this texture to the currently bound texture unit

	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load image, create texture
	int ground_texture_width, ground_texture_height;
	unsigned char* ground_image = SOIL_load_image("images/ground.jpg", &ground_texture_width, &ground_texture_height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ground_texture_width, ground_texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, ground_image);

	SOIL_free_image_data(ground_image); //free resources
	
	/*Bind ground into VAO and VBO*/
	GLuint ground_VAO, ground_VBO, color_VBO, groundUVsVBO;
	
	//FOR 3D: 
	glGenVertexArrays(1, &ground_VAO);
	glBindVertexArray(ground_VAO);
	
	// Bind the vertices buffer to the VAO: 
	glGenBuffers(1, &ground_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, ground_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ground_Vertices), &ground_Vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Bind the color buffer to the VAO: 
	glGenBuffers(1, &color_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, color_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ground_Color), &ground_Color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	
	glGenBuffers(1, &groundUVsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, groundUVsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ground_UVs), &ground_UVs, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);



	//references to uniforms
	projectionLoc = glGetUniformLocation(cubeShaderProgram, "projection_matrix");
	viewMatrixLoc = glGetUniformLocation(cubeShaderProgram, "view_matrix");
	transformLoc = glGetUniformLocation(cubeShaderProgram, "model_matrix");
	colorLoc = glGetUniformLocation(cubeShaderProgram, "color");
	viewPosLoc = glGetUniformLocation(cubeShaderProgram, "viewPos");

	teleportation_transformLoc = glGetUniformLocation(teleportationShaderProgram, "model_matrix");
	teleportation_colorLoc = glGetUniformLocation(teleportationShaderProgram, "in_color");
	teleportation_viewPosLoc = glGetUniformLocation(teleportationShaderProgram, "viewPos");

	car_projectionLoc = glGetUniformLocation(carShaderProgram, "projection_matrix");
	car_viewMatrixLoc = glGetUniformLocation(carShaderProgram, "view_matrix");
	car_transformLoc = glGetUniformLocation(carShaderProgram, "model_matrix");
	car_viewPosLoc = glGetUniformLocation(carShaderProgram, "viewPos");

	ground_projectionLoc = glGetUniformLocation(groundShaderProgram, "projection_matrix");
	ground_viewMatrixLoc = glGetUniformLocation(groundShaderProgram, "view_matrix");
	ground_transformLoc = glGetUniformLocation(groundShaderProgram, "model_matrix");
	ground_viewPosLoc = glGetUniformLocation(groundShaderProgram, "viewPos");

	building_projectionLoc = glGetUniformLocation(buildingShaderProgram, "projection_matrix");
	building_viewMatrixLoc = glGetUniformLocation(buildingShaderProgram, "view_matrix");
	building_transformLoc = glGetUniformLocation(buildingShaderProgram, "model_matrix");
	building_colourLoc = glGetUniformLocation(buildingShaderProgram, "colour_in");
	building_viewPosLoc = glGetUniformLocation(buildingShaderProgram, "viewPos");

	tree_projectionLoc = glGetUniformLocation(treeShaderProgram, "projection_matrix");
	tree_viewMatrixLoc = glGetUniformLocation(treeShaderProgram, "view_matrix");
	tree_transformLoc = glGetUniformLocation(treeShaderProgram, "model_matrix");

	/*Initialize the building (procedural modeling)*/
	buildings city(buildingShaderProgram);
	city.generateCity();

	glActiveTexture(GL_TEXTURE0); //select texture unit 0

	GLuint cube_texture;
	glGenTextures(1, &cube_texture);
	glBindTexture(GL_TEXTURE_2D, cube_texture); //bind this texture to the currently bound texture unit

	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load image, create texture and generate mipmaps
	int cube_texture_width, cube_texture_height;
	unsigned char* cube_image = SOIL_load_image("images/brick.jpg", &cube_texture_width, &cube_texture_height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cube_texture_width, cube_texture_height, 0, GL_RGB, GL_UNSIGNED_BYTE, cube_image);

	SOIL_free_image_data(cube_image);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	
	float angle = 0.0f;

	character characters = character();
	
	createManyTrees();
	
	collisions checkIfCollisions;

	//game loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//In 3D/real-World mode: 
		if (!teleportation_mode){
			
			movePlayer(window);			
			glm::mat4 view_matrix;

			if (survey_mode){

				camera_position = player_position + glm::vec3(0.0f, 0.40f, 0.0f);

				survey_camera_target = camera_position + glm::vec3(-3.0f * cos(y_rotation_angle + PI / 2), survey_target_change, 3.0f*sin(y_rotation_angle + PI / 2));
				//LookAt function: 
				view_matrix = glm::lookAt(camera_position, survey_camera_target, glm::vec3(0.0f, 1.0f, 0.0f));
			}
			else{
				//view_matrix = translate(view_matrix, camera_position);
				camera_position = player_position + glm::vec3(-3.0f * cos(y_rotation_angle - PI / 2), 0.4f, 3.0f*sin(y_rotation_angle - PI / 2));
				
				//camera_position = glm::vec3(0.0f,0.0f,-10.0f);

				view_matrix = glm::lookAt(camera_position, player_position + glm::vec3(0.0f, 0.30f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			}

			//draw skybox
			glUseProgram(skyboxShaderProgram);

			glm::mat4 skybox_view = glm::mat4(glm::mat3(view_matrix)); //remove the translation data
			glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(skybox_view));

			glUniformMatrix4fv(glGetUniformLocation(skyboxShaderProgram, "view_matrix"), 1, GL_FALSE, glm::value_ptr(skybox_view));
			glUniformMatrix4fv(glGetUniformLocation(skyboxShaderProgram, "projection_matrix"), 1, GL_FALSE, glm::value_ptr(projection_matrix));

			glUniform1i(glGetUniformLocation(skyboxShaderProgram, "skyboxTexture"), 1); //use texture unit 1

			glDepthMask(GL_FALSE);

			glBindVertexArray(skyboxVAO);
			glDrawArrays(GL_TRIANGLES, 0, skybox_vertices.size());
			glBindVertexArray(0);
			
			//Draw Ground
			
			glDepthMask(GL_TRUE);
			
			glm::mat4 model_matrix;
			glUseProgram(groundShaderProgram);

			glUniformMatrix4fv(ground_transformLoc, 1, GL_FALSE, glm::value_ptr(model_matrix));
			glUniformMatrix4fv(ground_viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(view_matrix));
			glUniformMatrix4fv(ground_projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));
			glUniformMatrix4fv(ground_viewPosLoc, 1, GL_FALSE, glm::value_ptr(camera_position));

			glUniform1i(glGetUniformLocation(groundShaderProgram, "groundTexture"), 2); //use texture unit 2
			
			glBindVertexArray(ground_VAO);
			glDrawArrays(GL_TRIANGLES, 0, 2 * 3);
			glBindVertexArray(0);

			//Draw city
			glUseProgram(buildingShaderProgram);

			// pass uniform matrices
			glUniformMatrix4fv(building_transformLoc, 1, GL_FALSE, glm::value_ptr(model_matrix)); //broadcast the uniform value to the shaders
			glUniformMatrix4fv(building_viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(view_matrix));
			glUniformMatrix4fv(building_projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));
			glUniformMatrix4fv(building_viewPosLoc, 1, GL_FALSE, glm::value_ptr(camera_position));

			glUniform1i(glGetUniformLocation(buildingShaderProgram, "cubeTexture"), 0);
			
			city.drawCity();
			
			//Draw Car

			glUseProgram(carShaderProgram);

			//glUniformMatrix4fv(car_transformLoc, 1, GL_FALSE, glm::value_ptr(model_matrix));
			glUniformMatrix4fv(car_viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(view_matrix));
			glUniformMatrix4fv(car_projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));
			glUniformMatrix4fv(car_viewPosLoc, 1, GL_FALSE, glm::value_ptr(camera_position));

			gamecars.drawCars(car_vertices, car_offsets, car_transformLoc);

			model_matrix = glm::mat4(1.0f);

			//draw model
			glUseProgram(cubeShaderProgram);

			
			glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(view_matrix));
			glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));
			glUniformMatrix4fv(viewPosLoc, 1, GL_FALSE, glm::value_ptr(camera_position));

			characters.drawHero(survey_mode, y_rotation_angle, modelVAO, colorLoc, transformLoc, model_vertices, player_position);
			
			//characters.setPosition(player_position);
			//characters.setCurrentVelocity(player_velocity);
			//Building and characters Collision detection 
			//DRAW CALL AND COLLISION DETECTION between main character and the buildings: 
			for (int i = 0; i < 30; i++)
			{
				checkIfCollisions.doCollisions(city.getRadius(), city.getMass(), city.getPosition(i), city.getCurrentVelocity(), characters.getRadius(), characters.getMass(), player_position, characters.getCurrentVelocity(), "wall");
				city.setCurrentVelocity(city.getCurrentVelocity());
				characters.setCurrentVelocity(characters.getCurrentVelocity());
			}

			//DRAW CALL AND COLLISION DETECTION between the main character and the normal characters: 
			for (int i = 0; i < numberOfCharacters; i++){

				glm::vec3 offset = 120.0f * caracter_offsets[i] - glm::vec3(60.0f, 0.0f, 60.0f);

				vec3 v = vec3(0.0f, 0.0f, 0.0f);

				checkIfCollisions.doCollisions(characters.getRadius(), characters.getMass(), offset, v, characters.getRadius(), characters.getMass(), player_position, characters.getCurrentVelocity(), "people");
				//city.setCurrentVelocity(city.getCurrentVelocity());
				characters.setCurrentVelocity(v);

				//model_matrix = glm::translate(model_matrix, offset);
				characters.drawNormalCharacter(angle, modelVAO, colorLoc, transformLoc, model_vertices, offset, color_offsets[i], color2_offsets[i]);

			}

			//glUniform1i(glGetUniformLocation(cubeShaderProgram, "cubeTexture"), 0); //use texture unit 0
			
			//trees
			glUseProgram(treeShaderProgram);

			glUniformMatrix4fv(tree_viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(view_matrix));
			glUniformMatrix4fv(tree_projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));

			//DRAW CALL AND COLLISION DETECTION between the main character and the trees: 
			for (int i = 0; i < numberOfTrees; i++) {
				
				glm::vec3 offset = 120.0f * tree_offsets[i] - glm::vec3(60.0f, 0.0f, 60.0f);
			
				drawTree(trunk[i], leaf[i], offset);

				checkIfCollisions.doCollisions(trunk[i].getRadius(), trunk[i].getMass(), offset, vec3(0.0f, 0.0f, 0.0f), characters.getRadius(), characters.getMass(), player_position, characters.getCurrentVelocity(), "wall");
				characters.setCurrentVelocity(characters.getCurrentVelocity());
			}


		}
		//In teleportation mode: 
		else{
			glUseProgram(teleportationShaderProgram);
			
			glm::mat4 model_matrix;
			glUniformMatrix4fv(teleportation_transformLoc, 1, GL_FALSE, glm::value_ptr(model_matrix));
			
			GLfloat color[4] = { 0.3f, 1.0f, 0.9f, 0.9f };
			
			glUniform4fv(teleportation_colorLoc, 1, color);

			glBindVertexArray(VAO2);

			glDrawElements(
				GL_TRIANGLES,// mode
				tele_screen_indices.size(),    // count
				GL_UNSIGNED_INT,   // type
				(void*)0           // element array buffer offset
				);
			glBindVertexArray(0);

			
			GLfloat color2[4] = { 1.0f, 0.1f, 0.1f, 1.0f };
			
			glUniform4fv(teleportation_colorLoc, 1, color2);
			
			model_matrix = glm::translate(model_matrix, glm::vec3(-1 * player_position.x / groundSize, player_position.z / groundSize, 0.0f));
			
			glUniformMatrix4fv(teleportation_transformLoc, 1, GL_FALSE, glm::value_ptr(model_matrix));
			
			glBindVertexArray(VAO3);
			
			glPointSize(10.0f);

			glDrawArrays(GL_POINTS, 0, 1);
		
			glBindVertexArray(0);
		}
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}

