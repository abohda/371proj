#version 330 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 UV;

out vec3 outNormal;
out vec3 fragPosition;
out vec3 outColor;
out vec2 outUV;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main()
{
	outNormal = vec3(0.0f,1.0f,0.0f); //rotate our normals
	outColor = color;
	fragPosition = vec3(model_matrix * vec4(position, 1.0f));
	outUV = UV;
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1.0f);
}