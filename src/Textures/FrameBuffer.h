#pragma once
#include "Textures/Texture.h"
class RenderBuffer;
class FrameBuffer{
	unsigned int id;
	TextureFile texture;
public:
	FrameBuffer(int w,int h,int type=GL_RGB,int fbtype=GL_COLOR_ATTACHMENT0):
		texture(TextureFile(GL_TEXTURE_2D,type,type))
	{
		glGenFramebuffers(1, &id);
		Bind();
		texture.Bind();
		texture.Texture2D(NULL, w, h);
		texture.setParam(GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		texture.setParam(GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, fbtype, GL_TEXTURE_2D, texture.GetID(), 0);
	}
	void Bind(){
		glBindFramebuffer(GL_FRAMEBUFFER,id);
	}
	void UnBind(){
		glBindFramebuffer(GL_FRAMEBUFFER,0);
	}
	bool CheckComplete(){
		return (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	}
	void AttachRenderBuffer(RenderBuffer& buffer,int type);
	unsigned int GetID(){
		return id;
	}
	TextureFile& GetTexture(){return texture;}
};
class RenderBuffer{
	unsigned int id;

	public:
	RenderBuffer(){
		glGenRenderbuffers(1, &id);
	}
	void Bind(){
		glBindRenderbuffer(GL_RENDERBUFFER, id);
	}
	void UnBind(){
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
	void Storage(int type,int w,int h){
		glRenderbufferStorage(GL_RENDERBUFFER,type,w,h); // use a single renderbuffer object for both a depth AND stencil buffer.
	}
	unsigned int getID(){
		return id;
	}
};
