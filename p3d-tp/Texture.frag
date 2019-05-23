#version 440 core
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D diffuse_texture;

void main() {

	FragColor = texture(diffuse_texture, TexCoord);

}
