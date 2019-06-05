#pragma once

#include <GL/glew.h>
#include <vector>

#include "GLUtils.h"

// class for element buffer abstrtaction
class IndexBuffer
{

private:

	// handle
	GLuint m_ebo;

	// the data
	std::vector<unsigned int> m_data;

	// handy data count
	int m_dataCount;

public:

	IndexBuffer(std::vector<unsigned int> data);
	~IndexBuffer();

	void Bind();

	void Unbind();

	// getter 
	int GetDataCount() { return m_dataCount; };

};