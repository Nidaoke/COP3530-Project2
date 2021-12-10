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

class Pyramid: public Primitive{
public:
	Pyramid():Primitive(){
		Vertex vertices[] = {
			//Position                     //Color                      //Texcoords            //Normal                     
			//front
			glm::vec3(0.0f, 0.5f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(.5f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.5f, -0.5f, 0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),

			//left
			glm::vec3(0.0f, 0.5f, 0.0f),  glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(.5f, 1.0f), glm::vec3(-1.0f, 0.0f, 1.0f),
			glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 1.0f),
			glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 1.0f),

			//back
			glm::vec3(0.0f, 0.5f, 0.0f),  glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(.5f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),

			//right
			glm::vec3(0.0f, 0.5f, 0.0f),  glm::vec3(1.0f, 1.0f, 0.0f), glm::vec2(.5f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
		};
		unsigned int nrOfVertices = sizeof(vertices)/sizeof(Vertex);

		this->set(vertices, nrOfVertices, nullptr, 0);
	}
};

class Cube: public Primitive
{
public:
	Cube()
		: Primitive()
	{
		Vertex vertices[] =
		{
			//Position								//Color							//Texcoords					//Normals
			glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
			glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

			glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, -1.f)
		};
		unsigned nrOfVertices = sizeof(vertices)/sizeof(Vertex);

		GLuint indices[] =
		{
			0, 1, 2,
			0, 2, 3,

			7, 6, 1,
			7, 1, 0,

			4, 5, 6,
			4, 6, 7,

			3, 2, 5,
			3, 5, 4
		};
		unsigned nrOfIndices = sizeof(indices)/sizeof(GLuint);

		this->set(vertices, nrOfVertices, indices, nrOfIndices);
	}
};

/*class Cube: public Primitive{
public:
	Cube():Primitive(){
		Vertex vertices[] = {
			//Position                     //Color                      //Texcoords            //Normal                     
			//front
			glm::vec3(-0.5f, 0.5f, 0.5f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(.5f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.5f, -0.5f, 0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.5f, -0.5f, 0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
			glm::vec3(-0.5f, 0.5f, 0.5f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(.5f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f),

			//left
			glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(.5f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-0.5f, 0.5f, 0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(.5f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f),

			//back
			glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(.5f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(.5f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f),

			//right
			glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.5f, 0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f),

			//top
			glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(.5f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.5f, 0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(-0.5f, 0.5f, 0.5f),  glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.5f, 0.5f, 0.5f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(.5f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f),

			//Bottom
			glm::vec3(0.5f, -0.5f, 0.5f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(.5f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(-0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec3(0.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.5f, -0.5f, 0.5f),  glm::vec3(1.0f, 0.0f, 0.0f), glm::vec2(.5f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f),
		};
		unsigned int nrOfVertices = sizeof(vertices)/sizeof(Vertex);

		this->set(vertices, nrOfVertices, nullptr, 0);
	}
};*/