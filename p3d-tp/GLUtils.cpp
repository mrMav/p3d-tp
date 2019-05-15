#include <GL/glew.h>

#include <iostream>

#include "GLUtils.h"

void GLUtils::CheckErrors()
{

	GLenum err;
	const GLubyte* errstring;

	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//errstring = gluErrorString(err);
		std::cout << "GL ERROR: "<< err << /* errstring << */ std::endl;
	}

}

GLUtils::GLUtils()
{
}
