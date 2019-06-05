#pragma once

#include <GL/glew.h>

// static class for checking gl errors
class GLUtils
{

public:

	static void CheckErrors();

private:
	
	GLUtils();  // disable the creation of an instance

};

