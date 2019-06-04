#pragma once

#include <stdio.h>
#include <vector>

#include "VertexPositionNormalTexture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Mesh.h"

class Model
{
public:

	glm::mat4 model;

	std::vector<Mesh*> meshes;

	Model();
	~Model();

	void Draw(glm::mat4 &view, glm::mat4 &projection, float deltatime);
};

