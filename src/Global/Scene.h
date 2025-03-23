#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

#include "../Shaders/ShaderProgram.h"
class Camera{
	glm::mat4 transform;
	glm::mat4 proj;
	float fov=45;
	float near;
	float far;
	float aspect;

	void recompute(){
		proj=glm::perspective(glm::radians(fov),aspect,near,far);
		//proj=glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.01f, 100.0f);
	}
	public:
	Camera(float aspect,glm::mat4 transform=glm::mat4(),float fov=45,float near=0.1,float far=100):
		transform(transform),fov(fov),near(near),far(far),aspect(aspect)
	{
		recompute();
	}
	void setFOV(float deg);
	void setAspect(float aspect);
	void setNear(float near);
	void setFar(float far);
	glm::mat4& getProjection(){
		return proj;
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
		static Scene instance(1920,1080);
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

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, -glm::vec3(0.0f, 0.0f, 3.0f)); 

		int proj;
		if((proj=program.getLocation("projection"))!=-1){
			program.setMat4f(proj,camera.getProjection());
		}
		
		int v;
		if((v=program.getLocation("view"))!=-1){
			program.setMat4f(v,view);
		}
	}
};
