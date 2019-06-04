/*

A material is assigned to a mesh.
When rendering, this material is activated.
A material is a class that holds the required maps and properties
for a shader to use.The shader will only one, a phong sahder.

Right.

So a material will have its own properties, but we also need
the properties of all the lights.For that we can create some
basic functions inside the shader to calculate some light types.

for this project, we will try to implement at least one of each the
following types of light:
1. ambient light;
2. directional liht;
3. omni light;
4. cone light;

*/

#pragma once
#include <stdio.h>
#include <string>

#include <glm\glm.hpp>

#include "Shader.h";
#include "Texture2D.h"



class Material
{
private:

	std::string m_name;

	Texture2D* m_diffuseMap;

public:
	
	Shader* shader;

	// Getter name
	std::string GetName() { return m_name; }

	// ambient color
	glm::vec3 Ka;

	// diffuse color
	glm::vec3 Kd;

	// specular color
	glm::vec3 Ks;

	// specular exponent
	float Ns;
	
	Material(std::string diffuse_filename);
	~Material();

	void Activate(glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection, float deltaTime);
};

