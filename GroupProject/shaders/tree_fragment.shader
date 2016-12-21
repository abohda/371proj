#version 330 core

in vec3 fragColor; // input the fragColor variable and 
uniform sampler2D cubeTexture;
in vec2 outUV;

out vec4 color; //output the color

void main()
{
	vec3 cubeColour = vec3(texture(cubeTexture, outUV));
	//color = vec4(fragColor,1.0f);
	color = vec4(cubeColour, 1.0f) + vec4(fragColor,1.0f);

} 

