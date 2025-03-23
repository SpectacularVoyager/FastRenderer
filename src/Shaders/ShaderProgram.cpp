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

void ShaderProgram::setFloat(std::string name,float val){
	int loc=getLocation(name);
	if(loc==-1)return;
	glUniform1f(loc,val);
}

int ShaderProgram::getLocation(std::string name){
	return glGetUniformLocation(id,name.c_str());
}

void ShaderProgram::setMat4f(std::string name,glm::mat4& matrix,int transpose){
	int loc=getLocation(name);
	if(loc==-1)return;
	glUniformMatrix4fv(loc,1,transpose,glm::value_ptr(matrix));
}
void ShaderProgram::setMat4f(int loc,glm::mat4& matrix,int transpose){
	glUniformMatrix4fv(loc,1,transpose,glm::value_ptr(matrix));
}
