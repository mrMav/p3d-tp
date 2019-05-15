#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

struct VertexPositionNormalTexture {

public:

	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture;

	VertexPositionNormalTexture(glm::vec3 pos, glm::vec3 norm, glm::vec2 tex)
	{
		this->position = pos;
		this->normal = norm;
		this->texture = tex;
	}

	std::string GetString() {

		std::string s;

		s.append("P: ");
		s.append(glm::to_string(this->position));

		s.append(" N: ");
		s.append(glm::to_string(this->normal));


		s.append(" T: ");
		s.append(glm::to_string(this->texture));

		return s;

	}

};

