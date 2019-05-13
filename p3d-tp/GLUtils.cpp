#include <GL/glew.h>

#include "GLUtils.h"

void GLUtils::CheckErrors()
{

	GLenum err;
	const GLubyte* errstring;

	while ((err = glGetError()) != GL_NO_ERROR)
	{
		//errstring = gluErrorString(err);
		printf("GL ERROR:%d %s", err /*, errstring */);
	}

}

GLUtils::GLUtils()
{
}
