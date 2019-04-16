#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdio.h>

#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

void errorCallbackFunction(int error, const char* description) {
	printf("ERROR %i: %s", error, description);
}

int main(void) {

	GLFWwindow* window;

	glfwSetErrorCallback(errorCallbackFunction);

	if (!glfwInit()) return -1;

	window = glfwCreateWindow(600, 540, "P3D-TP", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	glClearColor(1.0, 0.0, 1.0, 1.0);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;

}