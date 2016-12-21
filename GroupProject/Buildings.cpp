#include "Buildings.h"

//Constructor: 
buildings::buildings(GLuint buildingShaderProgram) {
	mass = 0.1; // default mass 
	radius = 10; //default radius 
	building_colourLoc = glGetUniformLocation(buildingShaderProgram, "colour_in");
}

//Generate the buildings: 
void buildings::generateBuilding(GLfloat x, GLfloat z, GLfloat width, GLfloat height, GLfloat depth){
	//Vertices determined based on provided parameters; bottom height is fixed
	vertices = {
		x - 0.5f * width, height, z + 0.5f * depth,
		x - 0.5f * width, -0.30f, z + 0.5f * depth,
		x + 0.5f * width, -0.30f, z + 0.5f * depth,

		x + 0.5f * width, -0.30f, z + 0.5f * depth,
		x + 0.5f * width, height, z + 0.5f * depth,
		x - 0.5f * width, height, z + 0.5f * depth,

		x + 0.5f * width, -0.30f, z + 0.5f * depth,
		x + 0.5f * width, -0.30f, z - 0.5f * depth,
		x + 0.5f * width, height, z - 0.5f * depth,

		x + 0.5f * width, height, z - 0.5f * depth,
		x + 0.5f * width, height, z + 0.5f * depth,
		x + 0.5f * width, -0.30f, z + 0.5f * depth,

		x - 0.5f * width, -0.30f, z + 0.5f * depth,
		x + 0.5f * width, -0.30f, z + 0.5f * depth,
		x + 0.5f * width, -0.30f, z - 0.5f * depth,

		x + 0.5f * width, -0.30f, z - 0.5f * depth,
		x - 0.5f * width, -0.30f, z - 0.5f * depth,
		x - 0.5f * width, -0.30f, z + 0.5f * depth,


		x - 0.5f * width, height, z - 0.5f * depth,
		x - 0.5f * width, -0.30f, z - 0.5f * depth,
		x + 0.5f * width, -0.30f, z - 0.5f * depth,

		x + 0.5f * width, -0.30f, z - 0.5f * depth,
		x + 0.5f * width, height, z - 0.5f * depth,
		x - 0.5f * width, height, z - 0.5f * depth,

		x - 0.5f * width, -0.30f, z + 0.5f * depth,
		x - 0.5f * width, -0.30f, z - 0.5f * depth,
		x - 0.5f * width, height, z - 0.5f * depth,

		x - 0.5f * width, height, z - 0.5f * depth,
		x - 0.5f * width, height, z + 0.5f * depth,
		x - 0.5f * width, -0.30f, z + 0.5f * depth,

		x - 0.5f * width, height, z + 0.5f * depth,
		x + 0.5f * width, height, z + 0.5f * depth,
		x + 0.5f * width, height, z - 0.5f * depth,

		x + 0.5f * width, height, z - 0.5f * depth,
		x - 0.5f * width, height, z - 0.5f * depth,
		x - 0.5f * width, height, z + 0.5f * depth
	};

	//Calculate normals for each face
	normals = {
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,

		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	//Provide UV values for each vertex
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

	//Push generated vertices to the city vector
	city.push_back(vertices);

	//Generate and bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//Generate and bind vertex VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//UV VBO
	glGenBuffers(1, &UVs_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, UVs_VBO);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Normals VBO
	glGenBuffers(1, &normals_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, normals_VBO);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(GLfloat), &normals.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(2);

	//Push the VAO and vertex VBO to their respective vectors
	VAOs.push_back(VAO);
	VBOs.push_back(VBO);

	//Push the building's position to the position vector (for collision detection)
	positions.push_back(vec3(x+width/2,-0.30+height/2,z+depth/2));
}
//Create random positions for the buildings: 
void buildings::generateCity(){
	//Initialize time
	srand(time(NULL));

	//For loop to generate 30 buildings
	for (int i = 0; i < 30; i++) {
		GLfloat w = 0, h = 0, d = 0;

		//Randomize x and z values of position
		GLfloat x = 1 + rand() % 99 - 50;
		GLfloat z = 1 + rand() % 99 - 50;

		//Randomize width, height and depth and 
		w = 3 + rand() % 10;
		h = 10 + rand() % 8;
		d = 3 + rand() % 10;

		//Call the generateBuilding method
		generateBuilding(x, z, w, h, d);

		//Randomize the colour
		GLfloat r = (rand() % 80) / 100.0f;
		GLfloat g = (rand() % 80) / 100.0f;
		GLfloat b = (rand() % 80) / 100.0f;

		glm::vec4 colour = glm::vec4(r, g, b, 1.0f);

		//Push the building's colour to a vector
		colours.push_back(colour);
	}
}
//draw call: 
void buildings::drawCity(){
	//For each building in the city vector:
	for (int i = 0; i < city.size(); i++) {
		//Pass the colour to the shaders
		glUniform4f(building_colourLoc, colours[i].x, colours[i].y, colours[i].z, colours[i].w);
		//Bind corresponding VAO
		glBindVertexArray(VAOs[i]);
		//Draw
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
	}
	glBindVertexArray(0);
}