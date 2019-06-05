#pragma once
#include <glm/glm.hpp>

class AmbientLight {

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
		shader->setVec3("ambLight.ambient", ambient);
		shader->setFloat("ambLight.intensity", intensity);

	}


};