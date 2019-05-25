#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture2D.h"
#include "Mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexPositionNormalTexture.h"
#include "Viewport.h"
#include "OrbitCamera.h"

void error_callback(int error, const char* description);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void process_input(GLFWwindow* window);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

int screenWidth = 800;
int screenHeight = 600;
float fov = 45.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = screenWidth / 2, lastY = screenHeight / 2;
float mouseYaw = 0.0f, mousePitch = 0.0f;
bool firstMouse = true;

Viewport viewport = Viewport(800, 600);
OrbitCamera camera = OrbitCamera(&viewport, glm::vec3(0), 5.0f, 45.0f);

int main(void) {
	
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);
	
	if (!glfwInit()) {
		
		return -1;
	
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(viewport.Width(), viewport.Height(), "P3D-TP", NULL, NULL);
	
	if (!window) {
		
		glfwTerminate();
		
		return -1;
	
	}

	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// print opengl profile info
	std::cout << glGetString(GL_VERSION) << " " << glGetString(GL_VENDOR) << " " << glGetString(GL_RENDERER) << std::endl;

	/*	
		init glew, and set some state for rendering
	*/

	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glViewport(0, 0, viewport.Width(), viewport.Height());

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	
	/* Define a cube geometry and colors */	
	std::vector<VertexPositionNormalTexture> vertices = {

		// positions          // rgb colors
		// front face         
		VertexPositionNormalTexture{-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f},
		VertexPositionNormalTexture{ 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f},
		VertexPositionNormalTexture{ 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f},
		VertexPositionNormalTexture{-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
		
		 // back face
		VertexPositionNormalTexture{ 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f},
		VertexPositionNormalTexture{-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 0.0f},
		VertexPositionNormalTexture{-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f},
		VertexPositionNormalTexture{ 0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 1.0f},

		// left face
		VertexPositionNormalTexture{-0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
		VertexPositionNormalTexture{-0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f,	1.0f, 0.0f},
		VertexPositionNormalTexture{-0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f,	1.0f, 1.0f},
		VertexPositionNormalTexture{-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,	0.0f, 1.0f},

		// right face
		VertexPositionNormalTexture{ 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f},
		VertexPositionNormalTexture{ 0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f},
		VertexPositionNormalTexture{ 0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f},
		VertexPositionNormalTexture{ 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f},

		// top face
		VertexPositionNormalTexture{-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f},
		VertexPositionNormalTexture{ 0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f},
		VertexPositionNormalTexture{ 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f},
		VertexPositionNormalTexture{-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f},

		// bottom face
		VertexPositionNormalTexture{-0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f, 0.0f, 0.0f},
		VertexPositionNormalTexture{ 0.5f, -0.5f,  0.5f,  0.0f, -1.0f, 0.0f, 1.0f, 0.0f},
		VertexPositionNormalTexture{ 0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f, 1.0f, 1.0f},
		VertexPositionNormalTexture{-0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f, 0.0f, 1.0f},
	
	};

	std::vector<int> indices = {

		// front face
		0, 1, 3,
		1, 2, 3,

		// back face
		4, 5, 7,
		5, 6, 7,

		// left face
		8, 9, 11,
		9, 10, 11,

		// right face
		12, 13, 15,
		13, 14, 15,

		// top face
		16, 17, 19, 
		17, 18, 19,  

		// bottom face
		20, 21, 23,  
		21, 22, 23  

	};

	Shader shader("Texture.vert", "Texture.frag");
	Texture2D woodBoxTexture("box-wood.png", GL_RGBA);
	Mesh cubeMesh { vertices, indices };
	
	while (!glfwWindowShouldClose(window)) {

		process_input(window);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		camera.Update(deltaTime);

		//cubeMesh.model = glm::rotate(cubeMesh.model, glm::radians(deltaTime * 1.5f), glm::vec3(0.0f, 1.0f, 0.0f));
		//cubeMesh.model = glm::rotate(cubeMesh.model, glm::radians(deltaTime * 1.5f), glm::vec3(1.0f, 0.0f, 0.0f));
		//cubeMesh.model = glm::rotate(cubeMesh.model, glm::radians(deltaTime * 1.5f), glm::vec3(0.0f, 0.0f, 1.0f));

		cubeMesh.Draw(camera.view_transform, camera.projection_transform, &shader, deltaTime);
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;

}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

	glViewport(0, 0, width, height);

	screenWidth = width;
	screenHeight = height;

}

void error_callback(int error, const char* description) {

	std::cout << "ERROR " << error << ": " << description;

}

void process_input(GLFWwindow* window) {

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {

		glfwSetWindowShouldClose(window, true);

	}


}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	if (firstMouse) {

		lastX = xpos;
		lastY = ypos;
		firstMouse = false;

	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
	
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

	camera.ProcessMouseScroll(yoffset);

}