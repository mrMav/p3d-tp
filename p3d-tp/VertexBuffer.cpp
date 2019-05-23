#include <stdio.h>
#include <vector>

#include "VertexBuffer.h"
#include "VertexPositionNormalTexture.h"

VertexBuffer::VertexBuffer(std::vector<VertexPositionNormalTexture> data)
{
	glGenBuffers(1, &m_vbo);
	GLUtils::CheckErrors();
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	GLUtils::CheckErrors();

	// build an interleaved array, with the received data
	size_t size = data.size() * 8;  // a vertexPositioNormalTexture has 8 floats
	// init data array
	m_data = (float*)malloc(size * sizeof(float));

	// populate
	for (int i = 0; i < data.size(); i++) {
		
		int offset = i * 8;

		m_data[0 + offset] = data[i].position.x;
		m_data[1 + offset] = data[i].position.y;
		m_data[2 + offset] = data[i].position.z;

		m_data[3 + offset] = data[i].normal.x;
		m_data[4 + offset] = data[i].normal.y;
		m_data[5 + offset] = data[i].normal.z;
				 
		m_data[6 + offset] = data[i].texture.x;
		m_data[7 + offset] = data[i].texture.y;
	}

	glBufferData(GL_ARRAY_BUFFER, size, m_data, GL_STATIC_DRAW);
	GLUtils::CheckErrors();
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_vbo);
	//GLUtils::CheckErrors();
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

