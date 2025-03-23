#pragma once
#include "glm/glm.hpp"
#include <glm/ext/matrix_float4x4.hpp>


#include "../Shaders/ShaderProgram.h"
#include "../Buffer/Buffer.h"
#include "../Global/Scene.h"

static float cubeVertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};


static float quadVertices[] = {
	-1.0f, -1.0f, 0.0f, 0.0f , 0.0f,
	-1.0f,  1.0f, 0.0f, 0.0f , 1.0f,
	1.0f, -1.0f, 0.0f, 1.0f , 0.0f,
	1.0f,  1.0f, 0.0f, 1.0f , 1.0f
};
static unsigned int quadIndices[] = {
	0, 2, 3,
	0, 1, 3
};  
class Cube{
	ShaderProgram shader;
	Buffer vertBuffer;
	VertexLayout layout;
	public:
	glm::mat4 transform;
	Cube(ShaderProgram& program):
		shader(program),transform(glm::mat4(1.0f))
	{
		this->vertBuffer=Buffer(GL_ARRAY_BUFFER,cubeVertices,sizeof(cubeVertices));
		layout.AddEntry(GL_FLOAT,sizeof(float),3);
		layout.AddEntry(GL_FLOAT,sizeof(float),2);
	}
	void Bind(){
		Scene::getScene().setGlobalUniforms(shader);
		vertBuffer.Bind();
		layout.Bind();
		shader.Use();
		shader.setMat4f("model",this->transform);
	}
	void Draw(){
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
};

class Icon{
	ShaderProgram shader;
	Buffer vertBuffer;
	Buffer indexBuffer;
	VertexLayout layout;
	public:
	glm::mat4 transform;
	Icon(ShaderProgram& program,glm::mat4 transform=glm::mat4(1.0f)):
		shader(program),transform(transform)
	{
		this->vertBuffer=Buffer(GL_ARRAY_BUFFER,quadVertices,sizeof(quadVertices));
		this->indexBuffer=Buffer(GL_ELEMENT_ARRAY_BUFFER,quadIndices,sizeof(quadIndices));
		layout.AddEntry(GL_FLOAT,sizeof(float),3);
		layout.AddEntry(GL_FLOAT,sizeof(float),2);
	}
	void Bind(){
		Scene::getScene().setGlobalUniforms(shader);
		vertBuffer.Bind();
		indexBuffer.Bind();
		layout.Bind();
		shader.Use();
		shader.setMat4f("model",this->transform);
	}
	void Draw(){
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL);
	}
};
