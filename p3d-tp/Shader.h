#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


/*
 * This is a helper class that handles all the shader stuff.
 * It loads all the source code from the given files, and compiles it to a gl program.
 * It will output any encountered errors.
 * This class is inspired by https://learnopengl.com/
 */
class Shader {

public:

	// program ID
	GLuint program;

	// constructor
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath) {

		using namespace std;

		string vertexCode;
		string fragmentCode;

		ifstream vShaderFile;
		ifstream fShaderFile;

		// ensure ifstream objects can throw exceptions
		vShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
		fShaderFile.exceptions(ifstream::failbit | ifstream::badbit);

		try {

			stringstream vShaderStream, fShaderStream;

			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);

			// reads file buffers to streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			// get string from buffer
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

		}
		catch (ifstream::failure e) {

			cout << "ERROR:SHADER::FILE_NOT_SUCCESSFULLY_READ" << endl;

		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// compile shaders
		GLuint vertex, fragment;
		int success;
		char infoLog[512];

		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

		if (!success) {

			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;

		}

		GLUtils::CheckErrors();

		// fragment shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

		if (!success) {

			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			cout << "ERROR::SHADER::FRAGMENT:COMPILATION_FAILED\n" << infoLog << endl;

		}

		GLUtils::CheckErrors();

		this->program = glCreateProgram();
		glAttachShader(this->program, vertex);
		glAttachShader(this->program, fragment);
		glLinkProgram(this->program);

		glGetProgramiv(this->program, GL_LINK_STATUS, &success);

		if (!success) {

			glGetProgramInfoLog(this->program, 512, NULL, infoLog);
			cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;

		}

		GLUtils::CheckErrors();

		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	// active this shader
	void use() {

		glUseProgram(this->program);

	}

	void setVec3(const std::string &name, const glm::vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);
		GLUtils::CheckErrors();
	}

	void setVec3(const std::string &name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);
		GLUtils::CheckErrors();
	}

	void setMat4(const std::string &name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
		GLUtils::CheckErrors();
	}
};
