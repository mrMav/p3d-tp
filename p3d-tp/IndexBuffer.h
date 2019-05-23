#pragma once

#include <GL/glew.h>
#include <vector>

#include "GLUtils.h"

class IndexBuffer
{

private:

	GLuint m_ebo;

	std::vector<int> m_data;

public:

	IndexBuffer(std::vector<int> data);
	~IndexBuffer();

	void Bind();

	void Unbind();

};