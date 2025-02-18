#pragma once
#include <glm/glm.hpp>

#include "BaseLight.h"

// directional light data container
class DirectionalLight : public BaseLight {

public:

	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	DirectionalLight(glm::vec3 dir, glm::vec3 amb, glm::vec3 diff, glm::vec3 spec) {

		ambient = amb;
		direction = dir;
		diffuse = diff;
		specular = spec;

	};

	~DirectionalLight() {

	};

	void SetShader(Shader* shader) {
		
		shader->use();
		shader->setInt("dirLight.isActive", isActive);
		shader->setVec3("dirLight.direction", direction);
		shader->setVec3("dirLight.ambient", ambient);
		shader->setVec3("dirLight.diffuse", diffuse);
		shader->setVec3("dirLight.specular", specular);

	}
	
};