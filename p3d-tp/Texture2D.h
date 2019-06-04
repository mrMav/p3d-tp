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

	Texture2D(const char* filename) {

		stbi_set_flip_vertically_on_load(true);
		
		unsigned char* data = stbi_load(filename, &width, &height, &channels, 0);

		if (data) {

			glActiveTexture(GL_TEXTURE0);

			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, channels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			
		}
		else {

			std::cout << "ERROR::TEXTURE2D::FAILED TO LOAD TEXTURE" << std::endl;

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