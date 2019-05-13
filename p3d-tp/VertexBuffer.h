#pragma once

#include <GL/glew.h>

#include "GLUtils.h"

class VertexBuffer
{

private:

	GLuint m_vbo;

public:
	
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind();

	void Unbind();


};

