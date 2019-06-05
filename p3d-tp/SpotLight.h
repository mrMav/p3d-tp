#pragma once
#include <glm/glm.hpp>

#include "Shader.h"
#include "BaseLight.h"

// spot light data container
class SpotLight : public BaseLight {

public:

	glm::vec3 position;
	glm::vec3 direction;

	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadractic;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	SpotLight(glm::vec3 pos, glm::vec3 dir) {

		position = pos;
		direction = dir;

		cutOff = glm::cos(glm::radians(10.0f));
		outerCutOff = glm::cos(glm::radians(20.0f));

		ambient = glm::vec3(0.1f);
		diffuse = glm::vec3(1.0f);
		specular = glm::vec3(1.0f);

		constant = 1.0f;
		linear = 0.1f;
		quadractic = 0.05;

	};

	~SpotLight() {

	};

	void SetShader(Shader* shader) {

		shader->use();

		shader->setInt("spotLight.isActive", isActive);

		shader->setVec3("spotLight.position", position);
		shader->setVec3("spotLight.direction", direction);

		shader->setFloat("spotLight.cutOff", cutOff);
		shader->setFloat("spotLight.outerCutOff", outerCutOff);
						 
		shader->setVec3("spotLight.ambient", ambient);
		shader->setVec3("spotLight.diffuse", diffuse);
		shader->setVec3("spotLight.specular", specular);

		shader->setFloat("spotLight.constant", constant);
		shader->setFloat("spotLight.linear", linear);
		shader->setFloat("spotLight.quadractic", quadractic);

	}

};