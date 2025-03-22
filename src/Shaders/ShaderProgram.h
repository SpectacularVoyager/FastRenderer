#pragma once

#include <fstream>
#include <iostream>
#include "string"
#include "GL/glew.h"
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
	void setFloat(char* name,float val);
	int getLocation(char* name);
};
