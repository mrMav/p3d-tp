#pragma once
#include <glm/glm.hpp>

#include "BaseLight.h"

// omni light data container
class OmniLight : public BaseLight {

public:

	glm::vec3 position;

	float constant;
	float linear;
	float quadractic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	OmniLight(glm::vec3 pos, glm::vec3 diff) {

		position = pos;

		ambient  = glm::vec3(0.1f);
		diffuse  = diff;
		specular = glm::vec3(1.0f);
		
		constant = 1.0f;
		linear = 0.1f;
		quadractic = 0.05;

	};

	~OmniLight() {

	};

	void SetShader(Shader* shader) {

		shader->use();
		
		shader->setInt("omniLight.isActive", isActive);

		shader->setVec3("omniLight.position", position);

		shader->setVec3("omniLight.ambient", ambient);
		shader->setVec3("omniLight.diffuse", diffuse);
		shader->setVec3("omniLight.specular", specular);

		shader->setFloat("omniLight.constant", constant);
		shader->setFloat("omniLight.linear", linear);
		shader->setFloat("omniLight.quadractic", quadractic);


	}

};