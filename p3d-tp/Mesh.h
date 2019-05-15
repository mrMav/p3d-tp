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
	
	Mesh(VertexPositionNormalTexture* vertices, int vertexCount, int* indices, int indicesCount);
	~Mesh();

};

