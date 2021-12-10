#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "Vertex.h"
#include "Primitives.h"
#include "Shader.h"
#include "Texture.h"
#include "Material.h"

class Mesh{
private:
	unsigned nrOfVertices;
	unsigned nrOfIndices;

	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 ModelMatrix;

	void initVAO(Primitive* primitive){
		//Set Variables
		this->nrOfVertices = primitive->getNrOfVertices();
		this->nrOfIndices = primitive->getNrOfIndices();

		//Create VAO
		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices*sizeof(Vertex), primitive->getVertices(), GL_STATIC_DRAW);

		if (this->nrOfIndices>0){
			glGenBuffers(1, &this->EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices*sizeof(GLuint), primitive->getIndices(), GL_STATIC_DRAW);
		}

		//POSITION
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);

		//COLOR
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);

		//TEXCOORD
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);

		//Normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);

		glBindVertexArray(0);
	}

	void initVAO(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices){
		//Set Variables
		this->nrOfVertices = nrOfVertices;
		this->nrOfIndices = nrOfIndices;
		
		//Create VAO
		glCreateVertexArrays(1, &this->VAO);
		glBindVertexArray(this->VAO);

		glGenBuffers(1, &this->VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
		glBufferData(GL_ARRAY_BUFFER, this->nrOfVertices*sizeof(Vertex), vertexArray, GL_STATIC_DRAW);

		if (this->nrOfIndices>0){
			glGenBuffers(1, &this->EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->nrOfIndices*sizeof(GLuint), indexArray, GL_STATIC_DRAW);
		}

		//POSITION
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
		glEnableVertexAttribArray(0);

		//COLOR
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
		glEnableVertexAttribArray(1);

		//TEXCOORD
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
		glEnableVertexAttribArray(2);

		//Normal
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
		glEnableVertexAttribArray(3);

		glBindVertexArray(0);
	}

	void updateUniforms(Shader* shader){
		shader->setMat4fv(this->ModelMatrix, "ModelMatrix");
	}

	void updateModelMatrix(){
		this->ModelMatrix = glm::mat4(1.0f);
		this->ModelMatrix = glm::translate(this->ModelMatrix, this->position);
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		this->ModelMatrix = glm::rotate(this->ModelMatrix, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		this->ModelMatrix = glm::scale(this->ModelMatrix, this->scale);
	}

public:
	Mesh(Vertex* vertexArray, const unsigned& nrOfVertices, GLuint* indexArray, const unsigned& nrOfIndices, glm::vec3 position = glm::vec3(0.0f), glm::vec3 rotation = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f)){
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;

		this->initVAO(vertexArray, nrOfVertices, indexArray, nrOfIndices);
		this->updateModelMatrix();
	}

	Mesh(
		Primitive* primitive,
		glm::vec3 position = glm::vec3(0.0f), 
		glm::vec3 rotation = glm::vec3(0.0f), 
		glm::vec3 scale = glm::vec3(1.0f)
	){
		this->position = position;
		this->rotation = rotation;
		this->scale = scale;

		this->initVAO(primitive);
		this->updateModelMatrix();
	}

	~Mesh(){
		glDeleteVertexArrays(1, &this->VAO);
		glDeleteBuffers(1, &this->VBO);
		if(this->nrOfIndices>0)
			glDeleteBuffers(1, &this->EBO);
	}

	//Accessors

	//Modifiers
	void setPosition(const glm::vec3 position){
		this->position = position;
	}

	void setRotation(const glm::vec3 rotation){
		this->rotation = rotation;
	}

	void setScale(const glm::vec3 scale){
		this->scale = scale;
	}

	//Functions
	void move(const glm::vec3 position){
		this->position += position;
	}

	void rotate(const glm::vec3 rotation){
		this->rotation += rotation; //FIX ROTATIONS
	}

	void scaleScale(const glm::vec3 scale){
		this->scale += scale;
	}

	void update(){

	}

	void render(Shader* shader){
		//Update Uniforms
		this->updateModelMatrix();
		this->updateUniforms(shader);

		shader->use();

		//Bind VAO
		glBindVertexArray(VAO);

		//Render
		if (this->nrOfIndices == 0)
			glDrawArrays(GL_TRIANGLES, 0, this->nrOfVertices);
		else
			glDrawElements(GL_TRIANGLES, this->nrOfIndices, GL_UNSIGNED_INT, 0);
	}
};