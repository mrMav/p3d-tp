#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_ebo);
	GLUtils::CheckErrors();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	GLUtils::CheckErrors();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	GLUtils::CheckErrors();
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_ebo);
	//GLUtils::CheckErrors();
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	GLUtils::CheckErrors();
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	GLUtils::CheckErrors();
}