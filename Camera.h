#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <SOIL2.h>

#include <iostream>

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

	}

public:
	Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 worldUp){

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
	void updateKeyboardInput(const float& dt, const int direction){
		//Update position vector
	}

	void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY){
		//update pitch yaw roll
	}

	void updateInput(const float& dt, const int direction, const double& offsetX, const double& offsetY){
		this->updateKeyboardInput(dt, direction);
		this->updateMouseInput(dt, offsetX, offsetY);
	}
};