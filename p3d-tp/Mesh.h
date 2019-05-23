#pragma once

#include <stdio.h>
#include <vector>

#include "VertexPositionNormalTexture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


class Mesh
{
private:

	GLuint m_vao;

	VertexBuffer* m_vertexBuffer;
	IndexBuffer* m_indexBuffer;

public:
	
	Mesh(std::vector<VertexPositionNormalTexture> vertices, std::vector<int> indices);
	~Mesh();

};

