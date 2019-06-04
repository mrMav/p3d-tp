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

#define OBJL_CONSOLE_OUTPUT
#include "OBJ_Loader.h"

#include "Texture2D.h"
#include "Mesh.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexPositionNormalTexture.h"
#include "Viewport.h"
#include "OrbitCamera.h"
#include "Model.h"

void error_callback(int error, const char* description);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void process_input(GLFWwindow* window);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Viewport viewport = Viewport(800, 600);
OrbitCamera camera = OrbitCamera(&viewport, glm::vec3(0), 5.0f, 45.0f);

/* cursor input properties*/
float lastX = viewport.Width() / 2;
float lastY = viewport.Height() / 2;
float mouseYaw = 0.0f;
float mousePitch = 0.0f;
bool firstMouse = true;

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


	Shader shader("Texture.vert", "Texture.frag");
	Texture2D woodBoxTexture("box-wood.png", GL_RGBA);

	/* load 3d model */
	objl::Loader loader;

	bool sucess = false;
	sucess = loader.LoadFile("Iron_Man/Iron_Man.obj");

	Model ironMan;
	Mesh ironMesh;


	if (sucess) {

		// if sucess, we can now build our own meshes with 
		// lets build the meshes
		for (int i = 0; i < loader.LoadedMeshes.size(); i++) {

			std::vector<VertexPositionNormalTexture> vertices;
			std::vector<unsigned int> indices;

			// create an array of our own vertexPositionNormalTexture
			for (int j = 0; j < loader.LoadedMeshes[i].Vertices.size(); j++) {

				objl::Vertex _v = loader.LoadedMeshes[i].Vertices[j];

				VertexPositionNormalTexture v{
					glm::vec3(_v.Position.X, _v.Position.Y, _v.Position.Z),
					glm::vec3(_v.Normal.X, _v.Normal.Y, _v.Normal.Z),
					glm::vec2(_v.TextureCoordinate.X , _v.TextureCoordinate.Y)
				};

				vertices.push_back(v);

			}

			// we will now build a indices vector.
			// the loaded indices are built in CCW
			// but we are using CW winding in this application
			for (int k = loader.LoadedMeshes[i].Indices.size() - 1; k >= 0; k--) {

				indices.push_back(loader.LoadedMeshes[i].Indices[k]);

			}

			Mesh* m = new Mesh(vertices, indices);
			m->shader = &shader;
			m->model = glm::scale(m->model, glm::vec3(0.5f));

			ironMan.meshes.push_back(m);

			//ironMesh = { vertices, loader.LoadedMeshes[i].Indices };
			//ironMesh.shader = &shader;

		}

	}
	else {

		printf("Loading error\n");
		//exit(-1);

	}


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

	std::vector<unsigned int> indices = {

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

	Mesh cubeMesh { vertices, indices };
	cubeMesh.shader = &shader;

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

		cubeMesh.Draw(camera.view_transform, camera.projection_transform, deltaTime);

		//ironMan.meshes[0]->Draw(camera.view_transform, camera.projection_transform, deltaTime);

		//ironMesh.Draw(camera.view_transform, camera.projection_transform, deltaTime);

		ironMan.Draw(camera.view_transform, camera.projection_transform, deltaTime);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	return 0;

}


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

	glViewport(0, 0, width, height);

	viewport.SetWidth(width);
	viewport.SetHeight(height);

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