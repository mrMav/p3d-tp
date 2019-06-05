/*
Shader inspiration and structure influence from:
https://learnopengl.com/Lighting/Multiple-lights
*/
#version 440 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform int isEffectActive;
uniform float time;

void main()
{
    // the fragment position in world position
	FragPos = vec3(model * vec4(a_position, 1.0));

	// transform the normal to world space using a normal matrix
	// (the transpose of the inverse of the upper-left corner of the model matrix)
    Normal = mat3(transpose(inverse(model))) * a_normal;  
    
	// passing the texture coord to the fragment shader
	TexCoord = a_uv;
    
	// calculate the base position in world of the vertex
	vec4 position = model * vec4(a_position, 1.0);

	if(isEffectActive == 1) {

		// deform vertex based on time
		float hI = (position.y / 2.0);  // influence of deformity based on height;
		float deformityX = sin(position.y * 10) * 0.1 * cos(time) * 0.8;
		float deformityY = sin(time) * (position.y / 2.0);
		float deformityZ = cos(position.y * 10) * 0.1 * sin(time) * 0.8;
		position.x += deformityX;
		position.y += deformityY;
		position.z += deformityZ;
	
	}

	// output position
    gl_Position = projection * view * vec4(position.xyz, 1.0);

}
