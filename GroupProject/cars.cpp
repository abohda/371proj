#include "cars.h"

//Default constructor: 
cars::cars(){
	mass = 0.2; //default mass
	radius = 0.75; //default radius
}

//Create cars: 
void cars::createCars(std::vector<glm::vec3> car_vertices, std::vector<glm::vec3> car_normals, std::vector<glm::vec3> car_color) {

	glGenVertexArrays(1, &carVAO);
	glBindVertexArray(carVAO);

	glGenBuffers(1, &carVerticesVBO);
	glBindBuffer(GL_ARRAY_BUFFER, carVerticesVBO);
	glBufferData(GL_ARRAY_BUFFER, car_vertices.size() * sizeof(glm::vec3), &car_vertices.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &carNormalsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, carNormalsVBO);
	glBufferData(GL_ARRAY_BUFFER, car_normals.size() * sizeof(glm::vec3), &car_normals.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &carColorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, carColorVBO);
	glBufferData(GL_ARRAY_BUFFER, car_color.size() * sizeof(glm::vec3), &car_color.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

}

void cars::drawCars(std::vector<glm::vec3> car_vertices, std::vector<glm::vec3> car_offsets, GLuint car_transformLoc) {

	glBindVertexArray(carVAO);

	glm::mat4 model_matrix;

	//Create cars at different location in the world: 
	for (int i = 0; i < car_offsets.size(); i++){

		glm::vec3 offset = 120.0f * car_offsets[i] - glm::vec3(60.0f, 0.0f, 60.0f);

		
		model_matrix = glm::translate(model_matrix, offset);

		glUniformMatrix4fv(car_transformLoc, 1, GL_FALSE, glm::value_ptr(model_matrix));

		//GLfloat carcolor[3] = { car_offsets[i].x, car_offsets[i].y, car_offsets[i].z };

		//glUniform3fv(car_altColorLoc, 1, carcolor);

		glDrawArrays(GL_TRIANGLES, 0, car_vertices.size());

		model_matrix = glm::mat4(1.0f);
	}


	glBindVertexArray(0);
}