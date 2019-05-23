#pragma once

#include <iostream>
#include <vector>
#include <string>

#include <GL/glew.h>

#include "stb_image.h"

#include "GLUtils.h"


class Texture2D {

public:

	GLuint textureID;

	int width, height, channels;

	Texture2D(const char* filename, GLint format) {

		stbi_set_flip_vertically_on_load(true);

		std::string path = "/" + std::string(filename);

		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		if (data) {

			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

		}
		else {

			std::cout << "ERROR::TEXTURE2D::FAILED TO LOAD TEXTURE:: " << path << std::endl;

		}

		GLUtils::CheckErrors();

		stbi_image_free(data);

	};

	void bind() {

		glBindTexture(GL_TEXTURE_2D, textureID);

	};

	void setParamenteri(GLenum pname, int pvalue) {

		bind();

		glTexParameteri(GL_TEXTURE_2D, pname, pvalue);

		GLUtils::CheckErrors();

	}

};