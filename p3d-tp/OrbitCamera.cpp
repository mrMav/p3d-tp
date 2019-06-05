#include <iostream>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "OrbitCamera.h"

OrbitCamera::OrbitCamera(Viewport* viewport_, glm::vec3 target, float offset, float fieldOfView)
{
	// init data

	mouse_sensitivity = 0.1f;
	pitch = 45.0f;
	yaw = 0.0f;

	field_view = fieldOfView;
	zoom = field_view;
	target_zoom = field_view;

	viewport = viewport_;

	offset_distance = offset;

	position = glm::vec3(0, 0, offset);
	this->target = target;

	view_transform = glm::mat4(1.0f);  // more superstition
	// I do know that the more recent versions already init the matrices
	// as identity, but you never know...
		
	projection_transform = glm::perspective(glm::radians(zoom), viewport->AspectRatio(), 0.1f, 1000.0f); // creates a perspective projection matrix

}


OrbitCamera::~OrbitCamera()
{
}

void OrbitCamera::Update(float deltatime) {

	// smooth pan
	if (target != target_target) target += (target_target - target) * deltatime;

	glm::vec4 pos = glm::vec4(0, 0, offset_distance, 1);

	// get the rotation matrices for rotating the camera around target
	glm::mat4 rotationX = glm::rotate(glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotationY = glm::rotate(glm::radians(yaw),   glm::vec3(0.0f, 1.0f, 0.0f));

	// transform the position with the pitch and yaw values
	pos = pos * rotationX; 
	pos = pos * rotationY;

	// target dependecy
	position = glm::vec3(pos) + target;

	// build new view matrix based on new position and target
	view_transform = glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));

	// smooth zooming
	if (zoom != target_zoom) zoom += (target_zoom - zoom) * deltatime; 

	// because we change the zoom, we need to refresh the perspective
	// the calculation of the ration must be done with the float cast
	// otherwise we lose precision and the result gets weird
	projection_transform = glm::perspective(glm::radians(zoom), viewport->AspectRatio(), 0.1f, 1000.0f);

}

void OrbitCamera::ProcessMouseMovement(float xoffset, float yoffset, bool isDragging, bool constrain_pitch) {

	// printf("Position: %s, Pitch: %f, Yaw: %f\n", glm::to_string(position).c_str(), xoffset, yoffset);	
	
	if (isDragging) {

		// if we are draggin, then we build a vector in the current view transform
		// what this will do, is add the representation of our 2d drag
		// to a 3d position

		float translation_factor = 0.2f;

		glm::vec4 translation = (glm::vec4{ -xoffset * mouse_sensitivity, -yoffset * mouse_sensitivity, 0.0f, 0.0f } * translation_factor) * view_transform;

		// we need to translate both position and target
		position += glm::vec3(translation);
		target_target += glm::vec3(translation);

	}
	else {

		// only rotate if not dragging!
		// this here will update the pitch and yaw

		xoffset *= mouse_sensitivity;
		yoffset *= mouse_sensitivity;

		yaw += xoffset;
		pitch -= yoffset;

		if (constrain_pitch) {

			if (pitch > 89.0f) pitch = 89.0f;

			if (pitch < -89.0f) pitch = -89.0f;
		}

	}

}

void OrbitCamera::ProcessMouseScroll(float wheelvalue) {

	// zoom in and out
	// we do not have dolly because we are lazy (as every programmer should be)

	if (target_zoom >= 1.0f && target_zoom <= 80.0f)
		target_zoom -= wheelvalue;

	if (target_zoom <= 1.0f)
		target_zoom = 1.0f;

	if (target_zoom >= 80.0f)
		target_zoom = 80.0f;
	
}