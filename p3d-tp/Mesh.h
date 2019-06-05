#pragma once

#include <stdio.h>
#include <vector>

#include "VertexPositionNormalTexture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Material.h"

// a mesh class to hold a pair of vertexbuffer and indexbuffer
// each mesh will have it's own material
// mesh is the only renderable
class Mesh
{
private:

	GLuint m_vao;

	VertexBuffer* m_vertexBuffer;
	IndexBuffer* m_indexBuffer;


public:
	
	// this mesh model matrix
	glm::mat4 model;

	// the material used when rendering
	Material* material;

	Mesh();
	Mesh(std::vector<VertexPositionNormalTexture> vertices, std::vector<unsigned int> indices);
	~Mesh();

	void Draw(glm::mat4 &view, glm::mat4 &projection, float deltaTime);

};

