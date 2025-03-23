#include "FrameBuffer.h"

void FrameBuffer::AttachRenderBuffer(RenderBuffer& buffer,int type){
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, type, GL_RENDERBUFFER, buffer.getID());
}
