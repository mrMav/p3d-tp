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

	/* build an interleaved array, with the received data */
	/* i think we could just use a pointer to the begining of the std::vector */

	// define the element count
	m_dataCount = data.size() * 8;  // a vertexPositioNormalTexture has 8 floats

	// calculate size of buffer in bytes
	size_t size = m_dataCount * sizeof(float);

	// init data array
	m_data = (float*)malloc(size);

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

	// after this, we can free the used data like this:
	// free(m_data);

}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_vbo);
	//GLUtils::CheckErrors();

	free(m_data);

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

