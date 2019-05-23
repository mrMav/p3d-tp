#include <stdio.h>
#include <vector>

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(std::vector<int> data)
{
	glGenBuffers(1, &m_ebo);
	GLUtils::CheckErrors();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	GLUtils::CheckErrors();
	
	m_data = data;

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_data.size() * sizeof(int), &m_data[0], GL_STATIC_DRAW);
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