#include <stdio.h>
#include <vector>

#include "Mesh.h"


// for now, we will assume that every mesh uses VertexPositionNormalTexture as the vertex data type
Mesh::Mesh(std::vector<VertexPositionNormalTexture> vertices, std::vector<int> indices)
{

	// generate VAO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	m_vertexBuffer = new VertexBuffer(vertices);
	//m_indexBuffer = new IndexBuffer(indices, indicesCount);
	   
	// set the locations for the shaders data:	
	// vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);

	//vertex normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));

	//vertex uv
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)));
	
}

Mesh::~Mesh()
{
	
}
