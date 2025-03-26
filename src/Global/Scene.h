#pragma once

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

#include "Shaders/ShaderProgram.h"
class Camera{
	glm::mat4 proj;
	float fov=45;
	float near;
	float far;
	float aspect;
	glm::vec3 position;
	glm::vec3 lookat;

	void recompute(){
		proj=glm::perspective(glm::radians(fov),aspect,near,far);
		//std::cout<<aspect<<std::endl;
		//proj=glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.01f, 100.0f);
	}
	public:
	Camera(float aspect,float fov=45,float near=0.1,float far=100):
		fov(fov),near(near),far(far),aspect(aspect)
	{
		position=glm::vec3(0.0f,0.0f,3.0f);
		lookat=glm::vec3(0.0f,0.0f,1.0f);
		recompute();
	}
	void setFOV(float deg);
	void setAspect(float aspect);
	void setNear(float near);
	void setFar(float far);
	glm::mat4& getProjection(){
		return proj;
	}
	glm::vec3& getPosition(){return position;}
	glm::vec3& getLookAt(){return lookat;}
	glm::mat4 getTransform(){
		return glm::lookAt(-position,glm::vec3(0.0),glm::vec3(0.0f,1.0f,0.0f));
	}
};

class Scene{
	int width;
	int height;
	Camera camera;
	Scene(int width,int height):
		width(width),height(height),
		camera(Camera((float)width/(float)height))
	{}
	public:
	static Scene& getScene()
	{
		static Scene instance(1080,720);
		return instance;
	}
	public:
	Scene(Scene const&)               = delete;
	void operator=(Scene const&)  = delete;
	public:
	int getWidth(){return width;}
	int getHeight(){return height;}
	void onResize(int width, int height);
	Camera& getCamera(){return camera;}
	void setGlobalUniforms(ShaderProgram& program){
		int proj;
		if((proj=program.getLocation("projection"))!=-1){
			program.setMat4f(proj,camera.getProjection());
		}
		
		int view;
		glm::mat4 cameraTransform=camera.getTransform();
		if((view=program.getLocation("view"))!=-1){
			program.setMat4f(view,cameraTransform);
		}
		// std::cout<<__FILE__<<__LINE__<<std::endl;
		int cam;
		if((cam=program.getLocation("cameraPos"))!=-1){
			// std::cout<<cam;
			glm::vec3 _v(1.0);
			glm::vec3 camPos=-camera.getPosition();
			program.setVec3f(cam,camPos);
		}
	}
	void PrepareFrameBufferRender(){
		glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void AfterFrameBufferRender(){
        glDisable(GL_DEPTH_TEST);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glDisable(GL_CULL_FACE);  
	}
};
