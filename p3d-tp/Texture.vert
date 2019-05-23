#version 440 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;

out vec3 Normal;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    
	Normal = a_normal;
	TexCoord = a_uv;
	gl_Position = projection * view * model * vec4(a_position, 1.0f);	

}
