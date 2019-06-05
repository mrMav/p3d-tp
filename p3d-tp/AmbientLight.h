#pragma once
#include <glm/glm.hpp>

#include "BaseLight.h"

// ambient light data container
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

	// sets the uniforms in the provided shader
	void SetShader(Shader* shader) {

		shader->use();
		shader->setInt("ambLight.isActive", isActive);
		shader->setVec3("ambLight.ambient", ambient);
		shader->setFloat("ambLight.intensity", intensity);

	}


};