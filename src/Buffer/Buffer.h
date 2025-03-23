#pragma once

#include <GL/glew.h>
#include <utility>
#include <vector>

class Buffer{
	int type;
	unsigned int id;
	void* data;
	int size;
	int usage;
public:
	Buffer(int type=GL_ARRAY_BUFFER,void* data=NULL,int size=0,unsigned int draw=GL_STATIC_DRAW):
		type(type),data(data),size(size),usage(draw)
	{
		glGenBuffers(1,&id);
	}
	void Data(void* data,int size);
	void Bind();
};

class VertexArray{
	unsigned int id;
public:
	VertexArray(){
		glGenVertexArrays(1,&id);
	}
	void Bind();
};
struct VertexLayoutEntry{
	int type;
	int stride;
	int n;
	VertexLayoutEntry(int type,int stride,int n):type(type),stride(stride),n(n){}
};
class VertexLayout{
	std::vector<VertexLayoutEntry> vec;
	unsigned char normalized=GL_FALSE;
public:
	void AddEntry(int type,int stride,int n);
	void Bind();
};
