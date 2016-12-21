#version 330 core
  
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec3 outNormal;
out vec3 fragPosition;
out vec3 outColor;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
//uniform vec3 altColor;

void main()
{
	
	outNormal = vec3(model_matrix * vec4(normal, 0.0f)); //rotate our normals
	
	//if(color.x != 1.0f)
		outColor = color;
	//else
	//	outColor = altColor;
		
	fragPosition = vec3(model_matrix * vec4(position, 1.0f));
	//out_offset = offset;
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1.0f);
}
