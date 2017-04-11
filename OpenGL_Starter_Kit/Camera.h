#ifndef CAMERA_H
#define CAMERA_H
#pragma once
#include "glm\glm.hpp"
#include "GL\glut.h"
#include <iostream>

class Camera
{
	protected:
		// Camera position
		glm::vec3 position;

		//Camera rotation
		glm::vec3 rotation;

		//Camera movement direction as vector
		glm::vec3 speed;

		double movementSpeedFactor;  //Controls how fast the camera moves
		double pitchSensitivity;  //Controls haw sensitive mouse movements affects look up/down
		double yawSensitivity; //Controls haw sensitive mouse movements affects look left/right


		//Camera properties for windows (near plane)
		int windowWidth;
		int windowHeight;
		int windowMidX;
		int windowMidY;

		void initCamera();

		public:
			static const double TO_RADS;  //This contains the value of 1 degree in radians

			const double Camera::toRads(const double &theAngleInDegrees) const;

			//Taking care of WASD event keys on keyboard
			bool holdingForward;
			bool holdingBackward;
			bool holdingLeftStrafe;
			bool holdingRightStrafe;
			
			//Constructor
			Camera(float windowWidth, float windowHeight);

			//Destructor
			~Camera();


			//Mouse movement handlers
			void handleMouseMove(int x, int y);

			const double toRad(const double &angleInDegree)  const;

			//moves the camera
			void move(double deltaTime);

			//Setters and getters
			float getPitchSensitivity() { return pitchSensitivity; };
			void setPitchSensitivity(float val) { pitchSensitivity = val; };
			float getYawSensitivity() { return yawSensitivity; };
			void setYawSensitivity(float val) { yawSensitivity = val; };

			glm::vec3 getPosition() { return position;  }
			glm::vec3 getRotation() { return rotation; }


};


#endif