#pragma once
#include "Shaders/ShaderProgram.h"
#include <vector>
#include <Textures/FrameBuffer.h>
#include "Meshes/ManualMesh.h"
#include <Renderer/Renderable.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
class Renderer{
	FrameBuffer fb;
	FrameBuffer shadow;
	int w,h;
	Icon quad;
	std::vector<Renderable*> objects;
	void RenderToFB();
public:
	Renderer(ShaderProgram& post,int w=1080,int h=720):
		fb(w,h),w(w),h(h),quad(post),
		shadow(SHADOW_WIDTH,SHADOW_HEIGHT,GL_DEPTH_COMPONENT,GL_DEPTH_ATTACHMENT,GL_FLOAT)
	{

		fb.Bind();
		RenderBuffer rb;
		rb.Bind();
		rb.Storage(GL_DEPTH24_STENCIL8,w,h);
		fb.AttachRenderBuffer(rb,GL_DEPTH_STENCIL_ATTACHMENT);
		if (!fb.CheckComplete()){
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		}
		fb.UnBind();

		shadow.Bind();
		shadow.GetTexture().setWrapAndFilter(GL_REPEAT,GL_REPEAT,GL_NEAREST,GL_NEAREST);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		shadow.UnBind();

	}
public:
	void Add(Renderable* r);
	void Loop();
	void RenderImGUI(ImGuiIO& io);
	void RenderShadow();
	void RenderScreenQuad();
};
