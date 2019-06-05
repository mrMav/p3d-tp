#include <stdio.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"

// epty constructor for declarations
Mesh::Mesh() {


}

// for now, we will assume that every mesh uses VertexPositionNormalTexture as the vertex data type
Mesh::Mesh(std::vector<VertexPositionNormalTexture> vertices, std::vector<unsigned int> indices)
{

	// generate VAO
	glGenVertexArrays(1, &m_vao);
	GLUtils::CheckErrors();
	glBindVertexArray(m_vao);
	GLUtils::CheckErrors();

	// create buffers
	m_vertexBuffer = new VertexBuffer(vertices);
	m_indexBuffer = new IndexBuffer(indices);

	// set the locations for the shaders data:	
	// vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)0);

	//vertex normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(3 * sizeof(float)));

	//vertex uv
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void*)(6 * sizeof(float)));

	GLUtils::CheckErrors();

	// aaand just because I'm superstitious, let's make sure the 
	// model matrix starts out as an identity matrix
	model = glm::mat4(1.0f);
}

Mesh::~Mesh()
{

}

void Mesh::Draw(glm::mat4 &view, glm::mat4 &projection, float deltaTime)
{
	// activate the material
	material->Activate(model, view, projection, deltaTime);

	// bind and draw call
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indexBuffer->GetDataCount(), GL_UNSIGNED_INT, 0);

}
