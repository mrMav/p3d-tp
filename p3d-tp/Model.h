#pragma once

#include <stdio.h>
#include <vector>

#include "VertexPositionNormalTexture.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Mesh.h"

// models are just containers for meshes
class Model
{
private:

	std::string m_directory;
	std::string m_filename;

public:
	
	std::vector<Mesh*> meshes;

	Model(std::string directory, std::string filename);
	~Model();

	void Draw(glm::mat4 &view, glm::mat4 &projection, float deltatime);
};

