#include "character.h"

//Default constructor: 
character::character(){
	mass = 2.0; //default mass
	radius = 0.6; //default radius 
}

void character::drawHero(bool &survey_mode, float &y_rotation_angle, GLuint &modelVAO, GLuint &colorLoc, GLuint &transformLoc, std::vector<glm::vec3> &model_vertices, glm::vec3 player_position)
{
	// Cube controls
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, player_position);
	model = glm::scale(model, cube_scale);
	model = glm::rotate(model, y_rotation_angle, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, x_rotation_angle, glm::vec3(1.0f, 0.0f, 0.0f));

	if (!survey_mode) {
		model = scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
		model = translate(model, glm::vec3(0.0f, 4.5f, -0.1f));

		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform4f(colorLoc, 0.871f, 0.722f, 0.529f, 1.0f);

		// Draw Head Cube
		glBindVertexArray(modelVAO);
		glDrawArrays(GL_TRIANGLES, 0, model_vertices.size());
		glBindVertexArray(0);

		// Cube controls
		model = glm::mat4(1.0f);

		model = glm::translate(model, player_position);
		model = glm::scale(model, cube_scale);
		model = glm::rotate(model, y_rotation_angle, glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, x_rotation_angle, glm::vec3(1.0f, 0.0f, 0.0f));
	}

	model = scale(model, glm::vec3(1.2f, 3.0f, 1.2f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));

	glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f);

	// Draw Body Rectangle
	glBindVertexArray(modelVAO);
	glDrawArrays(GL_TRIANGLES, 0, model_vertices.size());
	glBindVertexArray(0);

	// Cube controls
	model = glm::mat4(1.0f);

	model = glm::translate(model, player_position);
	model = glm::scale(model, cube_scale);
	model = glm::rotate(model, y_rotation_angle, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, x_rotation_angle, glm::vec3(1.0f, 0.0f, 0.0f));


	model = scale(model, glm::vec3(0.5f, 0.5f, 0.1f));
	model = translate(model, glm::vec3(0.0f, 4.0f, 12.0f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));

	glUniform4f(colorLoc, 1.0f, 1.0f, 0.f, 1.0f);

	// Draw Crest Rectangle
	glBindVertexArray(modelVAO);
	glDrawArrays(GL_TRIANGLES, 0, model_vertices.size());
	glBindVertexArray(0);

	// Cube controls
	model = glm::mat4(1.0f);

	model = glm::translate(model, player_position);
	model = glm::scale(model, cube_scale);
	model = glm::rotate(model, y_rotation_angle, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, x_rotation_angle, glm::vec3(1.0f, 0.0f, 0.0f));


	model = scale(model, glm::vec3(0.4f, 1.5f, 0.4f));
	model = translate(model, glm::vec3(4.0f, 0.9f, 0.0f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(colorLoc, 1.0f, 1.0f, 0.0f, 1.0f);


	// Draw Left Arm Rectangle
	glBindVertexArray(modelVAO);
	glDrawArrays(GL_TRIANGLES, 0, model_vertices.size());
	glBindVertexArray(0);

	// Cube controls
	model = glm::mat4(1.0f);

	model = glm::translate(model, player_position);
	model = glm::scale(model, cube_scale);
	model = glm::rotate(model, y_rotation_angle, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, x_rotation_angle, glm::vec3(1.0f, 0.0f, 0.0f));


	model = scale(model, glm::vec3(0.4f, 1.5f, 0.4f));
	model = translate(model, glm::vec3(-4.0f, 0.9f, 0.0f));

	/*	if (arm_rotation > ANGLE_LIMIT || arm_rotation <= 0.0f)
	{
	z_rotation_angle = -z_rotation_angle;
	arm_rotation += z_rotation_angle;
	}


	model = translate(model, pivot_point);
	model = glm::rotate(model, arm_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = translate(model, -pivot_point); */


	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(colorLoc, 1.0f, 1.0f, 0.0f, 1.0f);

	// Draw Right Arm Rectangle
	glBindVertexArray(modelVAO);
	glDrawArrays(GL_TRIANGLES, 0, model_vertices.size());
	glBindVertexArray(0);
}

void character::drawNormalCharacter(float &y_rotation_angle, GLuint &modelVAO, GLuint &colorLoc, GLuint &transformLoc, std::vector<glm::vec3> &model_vertices, glm::vec3 random_position, glm::vec3 bodyColor, glm::vec3 armColor){
	// Cube controls
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, random_position);
	model = glm::scale(model, cube_scale);
	model = glm::rotate(model, y_rotation_angle, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, x_rotation_angle, glm::vec3(1.0f, 0.0f, 0.0f));

	model = scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
	model = translate(model, glm::vec3(0.0f, 4.5f, -0.1f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(colorLoc, 0.871f, 0.722f, 0.529f, 1.0f);

	// Draw Head Cube
	glBindVertexArray(modelVAO);
	glDrawArrays(GL_TRIANGLES, 0, model_vertices.size());
	glBindVertexArray(0);

	// Cube controls
	model = glm::mat4(1.0f);

	model = glm::translate(model, random_position);
	model = glm::scale(model, cube_scale);
	model = glm::rotate(model, y_rotation_angle, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, x_rotation_angle, glm::vec3(1.0f, 0.0f, 0.0f));

	model = scale(model, glm::vec3(1.2f, 3.0f, 1.2f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));

	glUniform4f(colorLoc, bodyColor.x, bodyColor.y, bodyColor.z, 1.0f);

	// Draw Body Rectangle
	glBindVertexArray(modelVAO);
	glDrawArrays(GL_TRIANGLES, 0, model_vertices.size());
	glBindVertexArray(0);

	// Cube controls
	model = glm::mat4(1.0f);

	model = glm::translate(model, random_position);
	model = glm::scale(model, cube_scale);
	model = glm::rotate(model, y_rotation_angle, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, x_rotation_angle, glm::vec3(1.0f, 0.0f, 0.0f));


	model = scale(model, glm::vec3(0.5f, 0.5f, 0.1f));
	model = translate(model, glm::vec3(0.0f, 4.0f, 12.0f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));

	glUniform4f(colorLoc, armColor.x, armColor.y, armColor.z, 1.0f);

	// Draw Crest Rectangle
	glBindVertexArray(modelVAO);
	glDrawArrays(GL_TRIANGLES, 0, model_vertices.size());
	glBindVertexArray(0);

	// Cube controls
	model = glm::mat4(1.0f);

	model = glm::translate(model, random_position);
	model = glm::scale(model, cube_scale);
	model = glm::rotate(model, y_rotation_angle, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, x_rotation_angle, glm::vec3(1.0f, 0.0f, 0.0f));


	model = scale(model, glm::vec3(0.4f, 1.5f, 0.4f));
	model = translate(model, glm::vec3(4.0f, 0.9f, 0.0f));

	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(colorLoc, armColor.x, armColor.y, armColor.z, 1.0f);


	// Draw Left Arm Rectangle
	glBindVertexArray(modelVAO);
	glDrawArrays(GL_TRIANGLES, 0, model_vertices.size());
	glBindVertexArray(0);

	// Cube controls
	model = glm::mat4(1.0f);

	model = glm::translate(model, random_position);
	model = glm::scale(model, cube_scale);
	model = glm::rotate(model, y_rotation_angle, glm::vec3(0.0f, 1.0f, 0.0f));
	//model = glm::rotate(model, x_rotation_angle, glm::vec3(1.0f, 0.0f, 0.0f));


	model = scale(model, glm::vec3(0.4f, 1.5f, 0.4f));
	model = translate(model, glm::vec3(-4.0f, 0.9f, 0.0f));

	/*	if (arm_rotation > ANGLE_LIMIT || arm_rotation <= 0.0f)
	{
	z_rotation_angle = -z_rotation_angle;
	arm_rotation += z_rotation_angle;
	}


	model = translate(model, pivot_point);
	model = glm::rotate(model, arm_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	model = translate(model, -pivot_point); */


	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniform4f(colorLoc, armColor.x, armColor.y, armColor.z, 1.0f);

	// Draw Right Arm Rectangle
	glBindVertexArray(modelVAO);
	glDrawArrays(GL_TRIANGLES, 0, model_vertices.size());
	glBindVertexArray(0);
}
