#pragma once

#include <GL/glew.h>

#include "GLUtils.h"

class IndexBuffer
{

private:

	GLuint m_ebo;

public:

	IndexBuffer(const void* data, unsigned int size);
	~IndexBuffer();

	void Bind();

	void Unbind();


};