
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 UV;
layout (location = 2) in vec3 normal;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform vec4 colour_in;

out vec4 colour;
out vec2 outUV;
out vec3 out_normal;
out vec3 fragPosition;

void main()
{
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position.x, position.y, position.z, 1.0);
	colour = colour_in;
	out_normal = vec3(model_matrix * vec4(normal, 0.0f)); //rotate our normals
	outUV = UV;
	fragPosition = vec3(model_matrix * vec4(position, 1.0f));
}