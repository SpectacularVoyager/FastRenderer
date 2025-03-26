#pragma once
#include "Shaders/ShaderProgram.h"
#include <vector>
#include <Textures/FrameBuffer.h>
#include "Meshes/ManualMesh.h"
#include <Renderer/Renderable.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class Renderer{
	FrameBuffer fb;
	int w,h;
	Icon quad;
	std::vector<Renderable*> objects;
	void RenderToFB();
public:
	Renderer(ShaderProgram& post,int w=1080,int h=720):
		fb(w,h),w(w),h(h),quad(post)
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

	}
public:
	void Add(Renderable* r);
	void Loop();
	void RenderImGUI(ImGuiIO& io);
	void RenderShadow();
	void RenderScreenQuad();
};
