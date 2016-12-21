#version 330 core

in vec3 outNormal;
in vec3 outColor;
in vec3 fragPosition;
in vec2 outUV;
out vec4 color;

uniform sampler2D groundTexture;
uniform vec3 viewPos;

void main()
{
    vec3 lightColour = vec3(1.0f, 0.1f, 0.1f);
	vec3 cubeColour = vec3(texture(groundTexture, outUV));
	
	//ambient lighting
	float ambientStrength = 0.15f;
    vec3 ambient_contribution = ambientStrength * lightColour;
	
	//diffuse lighting
	vec3 light_position = vec3(0.0f, 0.0f, 2.0f); //world coords

	vec3 norm = normalize(outNormal);
	
	vec3 light_direction = normalize(light_position - fragPosition);
	float incident_degree = max(dot(norm, light_direction), 0.0f);
	vec3 diffuse_contribution = incident_degree * lightColour;

	// specular lighting 
	float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - fragPosition);
    vec3 reflectDir = reflect(-light_direction, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColour;  
	
	// The resulting colour is the contribtuion of each type of lights plus the colour of the object
	vec3 resultantColour = /*0.30f * */  (ambient_contribution + diffuse_contribution + specular) * cubeColour;
    color = vec4(resultantColour + outColor, 1.0f);
	
	//color = vec4(outColor, 1.0f);
} 