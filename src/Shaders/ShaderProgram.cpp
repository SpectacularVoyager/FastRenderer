#include "ShaderProgram.h"

void ShaderProgram::compile(){
	this->vert.compile();
	this->frag.compile();
	this->id=glCreateProgram();
	glAttachShader(this->id,vert.id);
	glAttachShader(this->id,frag.id);
	glLinkProgram(this->id);
	int success;
	glGetProgramiv(this->id, GL_LINK_STATUS, &success);
	char infoLog[512];
	if(!success) {
		glGetProgramInfoLog(this->id, 512, NULL, infoLog);
		std::cout<<"ERROR\n"<<infoLog<<"\n";
	}
	glUseProgram(this->id);
	glDeleteShader(this->vert.id);
	glDeleteShader(this->frag.id);
}
bool Shader::compile(){
	this->id=glCreateShader(this->type);
	const char* src=this->source.c_str();
	glShaderSource(this->id,1,&src,NULL);
	glCompileShader(this->id);
	return true;
}

void ShaderProgram::setFloat(char* name,float val){
	glUniform1f(getLocation(name),val);
}

int ShaderProgram::getLocation(char* name){
	return glGetUniformLocation(id,name);
}
