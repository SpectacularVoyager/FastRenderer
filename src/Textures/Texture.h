#pragma once

#include "../stb_image.h"
#include "GL/glew.h"
#include <glm/ext/matrix_float4x4.hpp>
#include <ostream>
#include <string>
#include <vector>
#include "Shaders/ShaderProgram.h"
#include "Buffer/Buffer.h"
#include "Global/Scene.h"

class Texture{
	protected:
	unsigned int id;
	int type;
	int w,h,src_fmt,dest_fmt;
	public:
	Texture(int type,int src_fmt,int dest_fmt):
			type(type),src_fmt(src_fmt),dest_fmt(dest_fmt)
	{
		glGenTextures(1,&id);
	}
	~Texture(){
		glDeleteTextures(1,&id);
	}
	void Bind(int id=0);
	void setParam(int key,int val);
	void setWrapAndFilter(int wraps,int wrapt,int mag,int min){
		setParam(GL_TEXTURE_WRAP_S, wraps);
		setParam(GL_TEXTURE_WRAP_T, wrapt);
		setParam(GL_TEXTURE_MAG_FILTER, mag);
		setParam(GL_TEXTURE_MIN_FILTER, min);
	}

	unsigned int GetID(){
		return id;
	}
};
class TextureFile:public Texture{
	void* data=NULL;
public:

	TextureFile(int type,int src_fmt,int dest_fmt):
		Texture(type,src_fmt,dest_fmt)
	{
	}
	void loadData(std::string file,int data_type=GL_UNSIGNED_BYTE){
		int channels;
		data=stbi_load(file.c_str(),&w,&h,&channels,3);
		glTexImage2D(GL_TEXTURE_2D, 0, dest_fmt, w, h, 0, src_fmt,data_type, data);
	}
	void Texture2D(void* data,int w,int h,int data_type){
		this->w=w;
		this->h=h;
		glTexImage2D(GL_TEXTURE_2D, 0, dest_fmt, w, h, 0, src_fmt, data_type, data);
	}
	~TextureFile(){
		if(data!=NULL)
			stbi_image_free(data);
	}
	void defaults(){
		setParam(GL_TEXTURE_WRAP_S, GL_REPEAT);
		setParam(GL_TEXTURE_WRAP_T, GL_REPEAT);
		setParam(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		setParam(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(type);
	}
};
static float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};
class CubeMapTexture{
	unsigned int id;
	public:
	CubeMapTexture(std::vector<std::string> files,std::string prefix=""){
		glGenTextures(1, &id);

		int width, height, nrChannels;
		unsigned char *data;  
		for(unsigned int i = 0; i < files.size(); i++)
		{
			std::string f=prefix+files[i];
			data = stbi_load(f.c_str(), &width, &height, &nrChannels, 0);
			if(data==NULL){return;}
			glTexImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
					0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
					);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);  
	}
	void Bind(){
		glBindTexture(GL_TEXTURE_CUBE_MAP, id);
	}
};
class CubeMap{
	ShaderProgram shader;
	Buffer vertBuffer;
	VertexLayout layout;
	public:
	glm::mat4 transform;
	CubeMap(ShaderProgram& program):
		shader(program),transform(glm::mat4(1.0f))
	{
		this->vertBuffer=Buffer(GL_ARRAY_BUFFER,skyboxVertices,sizeof(skyboxVertices));
		layout.AddEntry(GL_FLOAT,sizeof(float),3);
	}
	void Bind(){
		shader.Use();

		glm::mat4 view=Scene::getScene().getCamera().getTransform();
		view=glm::mat4(glm::mat3(view));
		shader.setMat4f("view",view);
		shader.setMat4f("projection",Scene::getScene().getCamera().getProjection());
		//Scene::getScene().setGlobalUniforms(shader);
		vertBuffer.Bind();
		layout.Bind();
		//shader.setMat4f("model",this->transform);
	}
	void Draw(){
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
};
