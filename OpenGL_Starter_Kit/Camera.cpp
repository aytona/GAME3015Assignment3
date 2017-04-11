#include "Camera.h"

const double Camera::TO_RADS = 3.141592 / 180.0;

Camera::Camera(float theWIndowWidth, float theWindowHeight)
{
	initCamera();
	windowWidth = theWIndowWidth;
	windowHeight = theWindowHeight;

	windowMidX = windowWidth / 2;
	windowMidY = windowHeight / 2;
	glutWarpPointer(windowMidX, windowMidY);
}


Camera::~Camera()
{
	// Clean up memory
	// We will take care of this later on
}

void Camera::initCamera()
{
	position = glm::vec3(0.0, 0.0, 0.5);
	rotation = glm::vec3(-90.0, 0.0, 0.0);
	speed = glm::vec3(0.0, 0.0, 0.0);

	//How fast the camera is travelling
	movementSpeedFactor = 40.0f;

	//To define how fast the camera responds to mouse movements
	pitchSensitivity = 0.2;
	yawSensitivity = 0.2;

	//Keyboard controls
	holdingForward = false;
	holdingBackward = false;
	holdingLeftStrafe = false;
	holdingRightStrafe = false;

}

//To convert degrees to radian
const double Camera::toRads(const double &theAngleInDegrees) const
{
	return theAngleInDegrees * TO_RADS;
}


void Camera::handleMouseMove(int mouseX, int mouseY)
{
	double horizMovment = (mouseX - windowMidX) * yawSensitivity;
	double vertMovment = (mouseY - windowMidY) * pitchSensitivity;

	std::cout << "Mid window values: " << windowMidX << "\t" << windowMidY << std::endl;
	std::cout << "Mouse values     : " << mouseX << "\t" << mouseY << std::endl;
	std::cout << horizMovment << "\t" << vertMovment << std::endl << std::endl;

	rotation.x = rotation.x + vertMovment;
	rotation.y = rotation.y + horizMovment;

	//Taking care of Limits
	if (rotation.x < -90)
	{
		rotation.x = -90;
	}

	if (rotation.x > 90)
	{
		rotation.x = 90;
	}

	if (rotation.y < 0)
	{
		rotation.y += 360;
	}

	if (rotation.y > 360)
	{
		rotation.y -= 360;
	}

	glutWarpPointer(windowMidX, windowMidY);

}


void Camera::move(double deltaTime)
{
	glm::vec3 movement;

	//get sin and cos of X and Y axis rotation
	double sinXRot = sin(toRads(rotation.x));
	double cosXRot = cos(toRads(rotation.x));

	double sinYRot = sin(toRads(rotation.y));
	double cosYRot = cos(toRads(rotation.y));


	double pitchLimitFactor = cosXRot; // Cancels out moving on Z axis when looking up/down

	if (holdingForward)
	{
		movement.x = movement.x + (sinYRot * pitchLimitFactor);
		movement.y = movement.y - sinXRot;
		movement.z = movement.z + (-cosYRot * pitchLimitFactor);
	}
	
	if (holdingBackward)
	{
		movement.x = movement.x - (sinYRot * pitchLimitFactor);
		movement.y = movement.y + sinXRot;
		movement.z = movement.z + (cosYRot * pitchLimitFactor);
		
	}

	if (holdingLeftStrafe)
	{
		movement.x = movement.x - cosYRot;
		movement.z = movement.z - sinYRot;
	}

	if (holdingRightStrafe)
	{
		movement.x = movement.x + cosYRot;
		movement.z = movement.z + sinYRot;
	}

	if (movement.x != 0 && movement.y !=0 && movement.z != 0)
	{
		movement = glm::normalize(movement);
	}

	double framerateIndependentFactor = movementSpeedFactor * deltaTime;

	movement *= framerateIndependentFactor;

 	position += movement;



}