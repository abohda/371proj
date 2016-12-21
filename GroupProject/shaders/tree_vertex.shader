#version 330 core
   
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec2 UV;

out vec3 fragColor; // use to pass to the fragment shader
out vec2 outUV;

uniform mat4 model_matrix;
uniform mat4 view_matrix; 
uniform mat4 projection_matrix;
															   
void main()
{
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1.0f);
	fragColor = vertexColor;
	outUV = UV;
}