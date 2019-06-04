#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "OrbitCamera.h"

OrbitCamera::OrbitCamera(Viewport* viewport_, glm::vec3 target, float offset, float fieldOfView)
{

	mouse_sensitivity = 0.1f;
	pitch = 45.0f;
	yaw = 0.0f;
	
	// basic initializations 
	field_view = fieldOfView;
	zoom = field_view;
	target_zoom = field_view;

	viewport = viewport_;

	offset_distance = offset;

	position = glm::vec3(0, 0, offset);
	this->target = target;

	view_transform = glm::mat4(1.0f);
		
	projection_transform = glm::perspective(glm::radians(zoom), viewport->AspectRatio(), 0.1f, 1000.0f); // creates a perspective projection matrix

}


OrbitCamera::~OrbitCamera()
{
}

void OrbitCamera::Update(float deltatime) {

	float midWidth  = viewport->Width()  / 2.0f;
	float midHeight = viewport->Height() / 2.0f;

	glm::vec4 pos = glm::vec4(0, 0, offset_distance, 1);

	glm::mat4 rotationX = glm::rotate(glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotationY = glm::rotate(glm::radians(yaw),   glm::vec3(0.0f, 1.0f, 0.0f));

	pos = pos * rotationX;
	pos = pos * rotationY;

	position = glm::vec3(pos) + target;

	view_transform = glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));

	// smooth zooming
	if (zoom != target_zoom) zoom += (target_zoom - zoom) * deltatime; 

	// because we change the zoom, we need to refresh the perspective
	// the calculation of the ration must be done with the float cast
	// otherwise we lose precision and the result gets weird
	projection_transform = glm::perspective(glm::radians(zoom), viewport->AspectRatio(), 0.1f, 1000.0f);

}

void OrbitCamera::ProcessMouseMovement(float xoffset, float yoffset, bool constrain_pitch) {

	xoffset *= mouse_sensitivity;
	yoffset *= mouse_sensitivity;

	yaw += xoffset;
	pitch -= yoffset;

	if (constrain_pitch) {

		if (pitch > 89.0f) pitch = 89.0f;

		if (pitch < -89.0f) pitch = -89.0f;
	}

	printf("Position: %s, Pitch: %f, Yaw: %f\n", glm::to_string(position).c_str(), xoffset, yoffset);

}

void OrbitCamera::ProcessMouseScroll(float wheelvalue) {

	if (target_zoom >= 1.0f && target_zoom <= 80.0f)
		target_zoom -= wheelvalue;

	if (target_zoom <= 1.0f)
		target_zoom = 1.0f;

	if (target_zoom >= 80.0f)
		target_zoom = 80.0f;
	
}