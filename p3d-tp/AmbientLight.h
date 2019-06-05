#pragma once
#include <glm/glm.hpp>

#include "BaseLight.h"

class AmbientLight : public BaseLight {

public:

	glm::vec3 ambient;
	
	float intensity;

	AmbientLight(glm::vec3 amb, float intens) {

		ambient = amb;
		intensity = intens;

	};

	~AmbientLight() {

	};


	void SetShader(Shader* shader) {

		shader->use();
		shader->setInt("ambLight.isActive", isActive);
		shader->setVec3("ambLight.ambient", ambient);
		shader->setFloat("ambLight.intensity", intensity);

	}


};