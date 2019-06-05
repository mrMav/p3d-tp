#include <stdio.h>
#include <vector>

#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(std::vector<unsigned int> data)
{

	// class constructor
	// creates the handles for gl objects

	glGenBuffers(1, &m_ebo);
	GLUtils::CheckErrors();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	GLUtils::CheckErrors();

	// sets the data 
	m_data = data;
	m_dataCount = data.size();

	// sends the data to gpu
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_data.size() * sizeof(unsigned int), &m_data[0], GL_STATIC_DRAW);
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