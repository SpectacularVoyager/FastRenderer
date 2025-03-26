#pragma once
#include "glm/glm.hpp"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/geometric.hpp>
#include <vector>


#include "Shaders/ShaderProgram.h"
#include "Buffer/Buffer.h"
#include "Global/Scene.h"

static float cubeVertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,	0.0,0.0,-1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0,0.0,-1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   0.0,0.0,-1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0,0.0,-1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0,0.0,-1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0,0.0,-1.0f,
    // Front face                                    ,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0,0.0,1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0,0.0,1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0,0.0,1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0,0.0,1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   0.0,0.0,1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0,0.0,1.0f,
    // Left face                                     ,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   -1.0f,0.0,0.0,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   -1.0f,0.0,0.0,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   -1.0f,0.0,0.0,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   -1.0f,0.0,0.0,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   -1.0f,0.0,0.0,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   -1.0f,0.0,0.0,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f,0.0,0.0,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f,0.0,0.0,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   1.0f,0.0,0.0,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f,0.0,0.0,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f,0.0,0.0,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f,0.0,0.0,
    // Bottom face                                   ,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0,-1.0f,0.0,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,   0.0,-1.0f,0.0,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0,-1.0f,0.0,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0,-1.0f,0.0,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0,-1.0f,0.0,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0,-1.0f,0.0,
    // Top face                                      ,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0,1.0f,0.0,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0,1.0f,0.0,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0,1.0f,0.0,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0,1.0f,0.0,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0,1.0f,0.0,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,   0.0,1.0f,0.0,
};


static float quadVertices[] = {
	-1.0f, -1.0f, 0.0f, 0.0f , 0.0f,
	-1.0f,  1.0f, 0.0f, 0.0f , 1.0f,
	1.0f, -1.0f, -0.0f, 1.0f , 0.0f,
	1.0f,  1.0f, -0.0f, 1.0f , 1.0f
};
static unsigned int quadIndices[] = {
	0, 3, 2,
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
		layout.AddEntry(GL_FLOAT,sizeof(float),3);
	}
	void Bind(){
		// std::cout<<__FILE__<<__LINE__<<std::endl;
		shader.Use();
		Scene::getScene().setGlobalUniforms(shader);
		vertBuffer.Bind();
		layout.Bind();
		shader.setMat4f("model",this->transform);
	}
	void Draw(){
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
};
struct VertexPlane{
	float position[3];
	float texCoord[2];
	float normal[3];
}__attribute__((packed));
struct Triangle{
	unsigned int a,b,c;
}__attribute__((packed));

class Plane{
	ShaderProgram shader;
	Buffer vertBuffer;
	Buffer indexBuffer;
	VertexLayout layout;
	public:
	glm::mat4 transform;
	unsigned int n;
	std::vector<VertexPlane> vertex;
	std::vector<Triangle> indices;
	Plane(ShaderProgram& program,int _n=10):
		shader(program),transform(glm::mat4(1.0f)),n(_n+1)
	{
		for(unsigned int i=0;i<n;i++){
			for(unsigned int j=0;j<n;j++){
				float max=n-1;
				VertexPlane v;
				v.position[0]=(2*i-max)/max;
				v.position[1]=0;
				v.position[2]=(2*j-max)/max;

				v.texCoord[0]=(i)/max;
				v.texCoord[1]=(j)/max;

				v.normal[0]=0;
				v.normal[1]=1;
				v.normal[2]=0;

				vertex.push_back(v);
			}	
		}
		indices.push_back((Triangle){.a=0,.b=1,.c=n});
		indices.push_back((Triangle){.a=1,.b=2,.c=n+1});
		for(unsigned int i=0;i<n-1;i++){
			for(unsigned int j=0;j<n-1;j++){
				unsigned int index=i*n+j;
				indices.push_back((Triangle){.a=index,.b=index+1,.c=index+n});
				indices.push_back((Triangle){.a=index+1,.b=index+n+1,.c=index+n});
			}
		}
		this->vertBuffer=Buffer(GL_ARRAY_BUFFER,vertex.data(),sizeof(VertexPlane)*vertex.size());
		this->indexBuffer=Buffer(GL_ELEMENT_ARRAY_BUFFER,indices.data(),sizeof(Triangle)*indices.size());
		layout.AddEntry(GL_FLOAT,sizeof(float),3);
		layout.AddEntry(GL_FLOAT,sizeof(float),2);
		layout.AddEntry(GL_FLOAT,sizeof(float),3);
	}
	void Bind(){
		// std::cout<<__FILE__<<__LINE__<<std::endl;
		shader.Use();
		Scene::getScene().setGlobalUniforms(shader);
		vertBuffer.Bind();
		indexBuffer.Bind();
		layout.Bind();
		shader.setMat4f("model",this->transform);
	}
	void Draw(){
		glDrawElements(GL_TRIANGLES,indices.size()*3,GL_UNSIGNED_INT,NULL);
	}
};
static void addPlane(unsigned int n,std::vector<VertexPlane>& vertex,std::vector<Triangle>& indices,glm::vec3 position){
		for(unsigned int i=0;i<n;i++){
			for(unsigned int j=0;j<n;j++){
				float max=n-1;
				glm::vec3 p((2*i-max)/max,0,(2*j-max)/max);
				p-=position;
				p=glm::normalize(p)/2.0f;
				VertexPlane v;
				v.position[0]=p.x;
				v.position[1]=p.y;
				v.position[2]=p.z;

				v.texCoord[0]=(i)/max;
				v.texCoord[1]=(j)/max;

				v.normal[0]=0;
				v.normal[1]=1;
				v.normal[2]=0;

				vertex.push_back(v);
			}	
		}
		for(unsigned int i=0;i<n-1;i++){
			for(unsigned int j=0;j<n-1;j++){
				unsigned int index=i*n+j;
				indices.push_back((Triangle){.a=index,.b=index+1,.c=index+n});
				indices.push_back((Triangle){.a=index+1,.b=index+n+1,.c=index+n});
			}
		}
}
class QuadSphere{
	ShaderProgram shader;
	Buffer vertBuffer;
	Buffer indexBuffer;
	VertexLayout layout;
	public:
	glm::mat4 transform;
	unsigned int n;
	std::vector<VertexPlane> vertex;
	std::vector<Triangle> indices;
	QuadSphere(ShaderProgram& program,int _n=10):
		shader(program),transform(glm::mat4(1.0f)),n(_n+1)
	{
		addPlane(n,vertex,indices,{0,-1,0});
		this->vertBuffer=Buffer(GL_ARRAY_BUFFER,vertex.data(),sizeof(VertexPlane)*vertex.size());
		this->indexBuffer=Buffer(GL_ELEMENT_ARRAY_BUFFER,indices.data(),sizeof(Triangle)*indices.size());
		layout.AddEntry(GL_FLOAT,sizeof(float),3);
		layout.AddEntry(GL_FLOAT,sizeof(float),2);
		layout.AddEntry(GL_FLOAT,sizeof(float),3);
	}
	void Bind(){
		// std::cout<<__FILE__<<__LINE__<<std::endl;
		shader.Use();
		Scene::getScene().setGlobalUniforms(shader);
		vertBuffer.Bind();
		indexBuffer.Bind();
		layout.Bind();
		shader.setMat4f("model",this->transform);
	}
	void Draw(){
		glDrawElements(GL_TRIANGLES,indices.size()*3,GL_UNSIGNED_INT,NULL);
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
		shader.Use();
		Scene::getScene().setGlobalUniforms(shader);
		vertBuffer.Bind();
		indexBuffer.Bind();
		layout.Bind();
		if(shader.getLocation("model")!=-1)
			shader.setMat4f("model",this->transform);
	}
	void Draw(){
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,NULL);
	}
};
