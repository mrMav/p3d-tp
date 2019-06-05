#pragma once

#include <stdio.h>
#include <vector>

#include <glm/glm.hpp>

#include "Viewport.h"

class OrbitCamera
{
public:
	
	// create variables to hold the current camera position and target
	glm::vec3 original_position;
	glm::vec3 position;
	glm::vec3 target_target;
	glm::vec3 target;

	
	// these are the matrices to be used when this camera is active
	glm::mat4 view_transform;
	glm::mat4 projection_transform;

	// the camera field of view
	float field_view;

	// for the rotation
	float pitch;
	float yaw;

	float mouse_sensitivity;

	float offset_distance;

	float zoom;
	float target_zoom;
	
	Viewport* viewport;

	OrbitCamera(Viewport* viewport_, glm::vec3 target, float offset, float fieldOfView);
	~OrbitCamera();

	void Update(float gametime);

	void ProcessMouseMovement(float xoffset, float yoffset, bool isDragging, bool constrain_pitch = true);

	void ProcessMouseScroll(float wheelvalue);


};

