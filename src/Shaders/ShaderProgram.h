#pragma once

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
	void compile();
	void setFloat(std::string,float val);
	void setMat4f(std::string,glm::mat4& matrix,int transpose=GL_FALSE);
	void setMat4f(int loc,glm::mat4& matrix,int transpose=GL_FALSE);

	int getLocation(std::string name);
};
