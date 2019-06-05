#pragma once
#include <glm/glm.hpp>

class DirectionalLight {

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
	
};