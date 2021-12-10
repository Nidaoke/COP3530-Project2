#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include "Vertex.h"

class Primitive{
private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
public:
	Primitive(){

	}

	virtual ~Primitive(){

	}

	//Functions
	void set(const Vertex* vertices, const unsigned nrOfVertices, const GLuint* indices, const unsigned nrOfIndices){
		for (size_t i = 0; i<nrOfVertices; i++){
			this->vertices.push_back(vertices[i]);
		}
		for (size_t i = 0; i<nrOfIndices; i++){
			this->indices.push_back(indices[i]);
		}
	}

	Vertex* getVertices(){
		return this->vertices.data();
	}

	GLuint* getIndices(){
		return this->indices.data();
	}

	const unsigned getNrOfVertices(){
		return this->vertices.size();
	}

	const unsigned getNrOfIndices(){
		return this->indices.size();
	}
};

class Quad: public Primitive{
public:
	Quad():Primitive(){
		Vertex vertices[] = {
			//Position                     //Color                      //Texcoords            //Normal                     
			glm::vec3(-0.5f, 0.5f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),

			glm::vec3(0.5f, 0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
		};
		unsigned int nrOfVertices = sizeof(vertices)/sizeof(Vertex);

		GLuint indices[] = {
			0, 1, 2,
			0, 2, 3
		};
		unsigned int nrOfIndices = sizeof(indices)/sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
private:

};

class Triangle: public Primitive{
public:
	Triangle():Primitive(){
		Vertex vertices[] = {
			//Position                     //Color                      //Texcoords            //Normal                     
			glm::vec3(-0.5f, 0.5f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.5f, -0.5f, 0.0f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),

			glm::vec3(0.5f, 0.5f, 0.0f),   glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
		};
		unsigned int nrOfVertices = sizeof(vertices)/sizeof(Vertex);

		GLuint indices[] = {
			0, 1, 2,
		};
		unsigned int nrOfIndices = sizeof(indices)/sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
private:

};