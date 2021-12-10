#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SOIL2.h>

#include <iostream>

enum direction{FORWARD = 0, BACK, LEFT, RIGHT};

class Camera{
private:
	glm::mat4 ViewMatrix;

	GLfloat movementSpeed;
	GLfloat sensitivity;

	glm::vec3 worldUp;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 right;
	glm::vec3 up;

	GLfloat pitch;
	GLfloat yaw;
	GLfloat roll;

	void updateCameraVectors(){
		this->front.x = cos(glm::radians(this->yaw))*cos(glm::radians(this->pitch));
		this->front.y = sin(glm::radians(this->pitch));
		this->front.z = sin(glm::radians(this->yaw))*cos(glm::radians(this->pitch));

		this->front = glm::normalize(this->front);
		this->right = glm::normalize(glm::cross(this->front, this->worldUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}

public:
	Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp){
		this->ViewMatrix = glm::mat4(1.0f);

		this->movementSpeed = 3.0f;
		this->sensitivity = 5.0f;

		this->worldUp = worldUp;
		this->position = position;
		this->right = glm::vec3(0.0f);
		this->up = worldUp;

		this->pitch = 0.0f;
		this->yaw = -90.0f;
		this->roll = 0.0f;

		this->updateCameraVectors();

	}

	~Camera(){

	}

	//Accessors
	const glm::mat4 getViewMatrix(){
		this->updateCameraVectors();
		
		this->ViewMatrix = glm::lookAt(this->position, this->position+this->front, this->up);

		return this->ViewMatrix;
	}

	const glm::vec3 getPosition() const{
		return this->position;
	}

	//Functions
	void move(const float& dt, const int direction){
		switch (direction){
			case FORWARD:
				this->position += this->front*this->movementSpeed*dt;
				break;
			case BACK:
				this->position -= this->front*this->movementSpeed*dt;
				break;
			case LEFT:
				this->position -= this->right*this->movementSpeed*dt;
				break;
			case RIGHT:
				this->position += this->right*this->movementSpeed*dt;
				break;
			default:
				break;
		}
	}

	void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY){
		//update pitch yaw roll
		this->pitch += static_cast<GLfloat>(offsetY)*this->sensitivity*dt*-1;
		this->yaw += static_cast<GLfloat>(offsetX)*this->sensitivity*dt;

		if (this->pitch>=80.0f)
			this->pitch = 80.0f;
		else if (this->pitch<=-80.0f)
			this->pitch = -80.0f;

		if (this->yaw>360.0f||this->yaw<-360.0f)
			this->yaw = 0;
	}

	void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY){
		this->updateMouseInput(dt, offsetX, offsetY);
	}
};