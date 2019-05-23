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

void error_callback(int error, const char* description);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void process_input(GLFWwindow* window);

int screenWidth = 800;
int screenHeight = 600;
float fov = 45.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float lastX = screenWidth / 2, lastY = screenHeight / 2;
float mouseYaw = 0.0f, mousePitch = 0.0f;
bool firstMouse = true;

int main(void) {

	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	VertexPositionNormalTexture p { glm::vec3(1.0, 2.0, 3.0), glm::vec3(0.0, 1.0, 0.0), glm::vec2(1.0, 0.5) };

	std::cout << p.GetString() << std::endl << std::endl;

	if (!glfwInit()) {
		
		return -1;
	
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(screenWidth, screenHeight, "P3D-TP", NULL, NULL);
	
	if (!window) {
		
		glfwTerminate();
		
		return -1;
	
	}

	glfwMakeContextCurrent(window);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	std::cout << glGetString(GL_VERSION) << " " << glGetString(GL_VENDOR) << " " << glGetString(GL_RENDERER) << std::endl;

	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW);
	glViewport(0, 0, screenWidth, screenHeight);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetCursorPosCallback(window, mouse_callback);   // TODO: add navigation
	//glfwSetScrollCallback(window, scroll_callback);
	
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
	
	glm::mat4 view  = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0, 0, -3.0f));  // translates the camera back
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f); // creates a perspective projection matrix
	
	while (!glfwWindowShouldClose(window)) {

		process_input(window);

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		glClearColor(0.1, 0.1, 0.1, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		cubeMesh.model = glm::rotate(cubeMesh.model, glm::radians(deltaTime * 20), glm::vec3(0.0f, 1.0f, 0.0f));
		cubeMesh.model = glm::rotate(cubeMesh.model, glm::radians(deltaTime * 20), glm::vec3(1.0f, 0.0f, 0.0f));
		cubeMesh.model = glm::rotate(cubeMesh.model, glm::radians(deltaTime * 20), glm::vec3(0.0f, 0.0f, 1.0f));

		cubeMesh.Draw(view, projection, &shader, deltaTime);
		
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