#pragma once

#include <GL/glew.h>
#include <vector>

#include "GLUtils.h"

class IndexBuffer
{

private:

	GLuint m_ebo;

	std::vector<unsigned int> m_data;

	int m_dataCount;

public:

	IndexBuffer(std::vector<unsigned int> data);
	~IndexBuffer();

	void Bind();

	void Unbind();

	int GetDataCount() { return m_dataCount; };

};