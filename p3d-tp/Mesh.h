#pragma once

#include <stdio.h>
#include <vector>

#include "VertexPositionNormalTexture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"

class Mesh
{
private:

	GLuint m_vao;

	VertexBuffer* m_vertexBuffer;
	IndexBuffer* m_indexBuffer;


public:

	glm::mat4 model;
	Shader* shader;

	Mesh();
	Mesh(std::vector<VertexPositionNormalTexture> vertices, std::vector<unsigned int> indices);
	~Mesh();

	void Draw(glm::mat4 &view, glm::mat4 &projection, float deltaTime);

};

