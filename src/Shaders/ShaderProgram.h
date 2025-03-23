#pragma once

#include <filesystem>
#include <fstream>
#include <glm/ext/matrix_float4x4.hpp>
#include <iostream>
#include "string"
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
class Shader{
	GLenum type;
	std::string source;

public:
	unsigned int id;
	Shader(std::string file,GLenum type):type(type){
		std::ifstream stream(file);
		if(!std::filesystem::exists(file)){
			std::cout<<"FILE: ["<<file<<"] DOES NOT EXIST\n";
			return;
		}
		while(!stream.eof()){
			std::string line;

			std::getline(stream,line);
			source+=line+"\n";
		}
	}
	bool compile();
};
class ShaderProgram{
	Shader vert;
	Shader frag;
public:
	unsigned int id;
	ShaderProgram(std::string vs,std::string fs):
		vert(Shader(vs,GL_VERTEX_SHADER)),
		frag(Shader(fs,GL_FRAGMENT_SHADER))
	{}
	~ShaderProgram(){
		glDeleteProgram(id);
	}
	void compile();
	void setFloat(std::string,float val);
	void setInt(std::string,int val);
	void setInt(int loc,int val);
	void setVec3f(std::string,glm::vec3 vec);
	void setVec3f(int loc,glm::vec3& vec);
	void setMat4f(std::string,glm::mat4& matrix,int transpose=GL_FALSE);
	void setMat4f(int loc,glm::mat4& matrix,int transpose=GL_FALSE);
	void Use(){
		glUseProgram(this->id);
	}

	int getLocation(std::string name);
};
