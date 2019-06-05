#pragma once

// a starting point for all the lights that will be used
class BaseLight {

public:

	// tells if this light is switch one or off
	// values other than 1 mean off;
	int isActive;

	BaseLight()
	{
		isActive = 1;  // switch on when creating
	}

};