#version 330 core

out vec4 frag_colour;

in vec4 colour;
in vec2 outUV;
in vec3 out_normal;
in vec3 fragPosition;


uniform sampler2D cubeTexture;
uniform vec3 viewPos;

void main()
{ 
	vec3 lightColour = vec3(1.0f, 0.1f, 0.1f);
	vec3 cubeColour = vec3(texture(cubeTexture, outUV));
	
	float ambientStrength = 0.15f;
    vec3 ambient_contribution = ambientStrength * lightColour;
	
	//diffuse lighting
	vec3 light_position = vec3(0.0f, 0.0f, 2.0f); //world coords

	vec3 norm = normalize(out_normal);
	
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
	vec3 resultantColour = (ambient_contribution + diffuse_contribution + specular)* cubeColour;
    
	//frag_colour = colour;
	frag_colour = vec4(resultantColour, 1.0f) + colour;//ambient lighting
}  
 
	