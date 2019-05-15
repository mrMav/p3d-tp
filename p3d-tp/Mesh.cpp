#include "Mesh.h"

Mesh::Mesh(VertexBuffer* vbo, IndexBuffer* ebo)
{

	// generate VAO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	m_vertexBuffer = vbo;
	m_indexBuffer = ebo;

}


Mesh::~Mesh()
{
	
}
