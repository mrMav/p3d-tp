#include <stdio.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"

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

	model = glm::mat4(1.0f);
}

Mesh::~Mesh()
{

}

void Mesh::Draw(glm::mat4 &view, glm::mat4 &projection, float deltaTime)
{

	shader->use();
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);

	m_vertexBuffer->Bind();
	glDrawElements(GL_TRIANGLES, m_indexBuffer->GetDataCount(), GL_UNSIGNED_INT, 0);

}
