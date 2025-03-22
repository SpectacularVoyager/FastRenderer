#pragma once

#include "../stb_image.h"
#include "GL/glew.h"
#include <string>

class Texture{
	unsigned int id;
	int type;
	void* data;
	int w,h,src_fmt,dest_fmt;
	public:
	Texture(int type,std::string file,int src_fmt,int dest_fmt,int channels):
			type(type),src_fmt(src_fmt),dest_fmt(dest_fmt)
	{
		int img_channels;
		data=stbi_load(file.c_str(),&w,&h,&channels,channels);
		glGenTextures(1,&id);
	}
	~Texture(){
		stbi_image_free(data);
	}
	void Bind(int id=0);
	void setParam(int key,int val);
	void Texture2D(){
		setParam(GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		setParam(GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		setParam(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		setParam(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(type, 0, dest_fmt, w, h, 0, src_fmt, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(type);
	}

};
