#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_vbo);
	GLUtils::CheckErrors();
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	GLUtils::CheckErrors();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	GLUtils::CheckErrors();	
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_vbo);
	GLUtils::CheckErrors();
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	GLUtils::CheckErrors();
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	GLUtils::CheckErrors();
}

