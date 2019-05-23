#pragma once

#include <GL/glew.h>

#include <stdio.h>
#include <vector>

#include "GLUtils.h"
#include "VertexPositionNormalTexture.h"

class VertexBuffer
{

private:

	GLuint m_vbo;

	// will hold the data
	// we will decompose the received data to an interleaved array
	float* m_data;
	int m_dataCount;

public:
	
	VertexBuffer(std::vector<VertexPositionNormalTexture> data);  // later we can add support for other vertex types
	~VertexBuffer();

	void Bind();

	void Unbind();
	
};

