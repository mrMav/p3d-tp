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

	Mesh(std::vector<VertexPositionNormalTexture> vertices, std::vector<int> indices);
	~Mesh();

	void Draw(glm::mat4 &view, glm::mat4 &projection, Shader *shader, float deltaTime);

};

