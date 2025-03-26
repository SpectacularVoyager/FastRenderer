#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <glm/detail/qualifier.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Buffer/Buffer.h"
#include "Textures/Texture.h"
#include "Global/Scene.h"
#include "Meshes/ManualMesh.h"
#include "Shaders/ShaderProgram.h"
#include "Textures/FrameBuffer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar* msg, const void* data);

bool wire=false;
void processInput(GLFWwindow* window){
	if(glfwGetKey(window,GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window,true);
	if(glfwGetKey(window,GLFW_KEY_TAB)){
		glPolygonMode( GL_FRONT_AND_BACK, (wire)?GL_LINE:GL_FILL);
	}
	wire=!wire;
}

void onResize(GLFWwindow* window,int x,int y){
	Scene::getScene().onResize(x,y);
}
int main(void)
{
    GLFWwindow* window;

    if (glfwInit()==GLFW_FALSE)
        return -1;

    window = glfwCreateWindow(Scene::getScene().getWidth(), Scene::getScene().getHeight(), "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
		std::cout<<"Failed To Create OpenGL Window\n";
        return -1;
    }
    glfwMakeContextCurrent(window);
	GLenum err = glewInit();
	if(!err){
		std::cout<<"COULD NOT INIT GLEW\n";
	}
    glEnable(GL_DEBUG_OUTPUT);
	// glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glEnable( GL_BLEND );
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);  
	glEnable(GL_CULL_FACE);  
	glCullFace(GL_BACK);  
    glDebugMessageCallback(GLDebugMessageCallback, NULL);

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSetWindowSizeCallback(window, onResize);
	VertexArray array;
	array.Bind();

	ShaderProgram shader("res/shaders/blinnPhong/vert.glsl","res/shaders/blinnPhong/frag.glsl");
	shader.compile();
	ShaderProgram unlit("res/shaders/unlitSprite/vert.glsl","res/shaders/unlitSprite/frag.glsl");
	unlit.compile();
	ShaderProgram skybox("res/shaders/skybox/vert.glsl","res/shaders/skybox/frag.glsl");
	skybox.compile();

	TextureFile texture(GL_TEXTURE_2D,GL_RGB,GL_RGB);
	texture.Bind(2);
	texture.loadData("res/images/proto/PNG/Dark/texture_04.png");
	texture.defaults();
	TextureFile textureIcon(GL_TEXTURE_2D,GL_RGBA,GL_RGBA);
	textureIcon.Bind(1);
	textureIcon.loadData("res/images/icon.png");
	texture.defaults();

	shader.Use();

	ShaderProgram quadShader("res/shaders/quad/vert.glsl","res/shaders/quad/frag.glsl");
	quadShader.compile();


	Cube cube(shader);
	cube.transform*=glm::scale(glm::mat4(1.0f),glm::vec3(0.5));
	Icon icon(unlit,glm::translate(glm::scale(glm::mat4(1.0f),glm::vec3(0.2f)),glm::vec3(4.0f,0.0f,0.0f)));
	Icon icon2(unlit,glm::translate(glm::scale(glm::mat4(1.0f),glm::vec3(0.2f)),glm::vec3(-4.0f,0.0f,0.0f)));

	CubeMap map(skybox);
	CubeMapTexture skyboxTexture({"right.jpg","left.jpg","top.jpg","bottom.jpg","front.jpg","back.jpg"},"res/images/skybox/");
	skyboxTexture.Bind();
	float rot=0;
	Icon quad(quadShader);


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);

    ImGui_ImplOpenGL3_Init("#version 330");
	float speed=.5;

	int SCR_HEIGHT=720,SCR_WIDTH=1080;

	FrameBuffer fb(SCR_WIDTH,SCR_HEIGHT);
	fb.Bind();
	RenderBuffer rb;
	rb.Bind();
	rb.Storage(GL_DEPTH24_STENCIL8,SCR_WIDTH,SCR_HEIGHT);
	fb.AttachRenderBuffer(rb,GL_DEPTH_STENCIL_ATTACHMENT);
    if (!fb.CheckComplete()){
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	}
	fb.UnBind();

	FrameBuffer shadow(1024,1024,GL_DEPTH_COMPONENT,GL_DEPTH_ATTACHMENT,GL_FLOAT);
	shadow.GetTexture().setWrapAndFilter(GL_REPEAT,GL_REPEAT,GL_NEAREST,GL_NEAREST);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	shadow.UnBind();
	Plane floor(shader,8);
	floor.transform*=glm::translate(glm::mat4(1.0),glm::vec3(0,-1.0,0));
	floor.transform*=glm::scale(glm::mat4(1.0),glm::vec3(5.0));

    while (!glfwWindowShouldClose(window))
    {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		processInput(window);
		rot-=glm::radians(speed);
		//fb.Bind();
		//Scene::getScene().PrepareFrameBufferRender();
		// glViewport(0, 0, 1024, 1024);
		// shadow.Bind();
		// glClear(GL_DEPTH_BUFFER_BIT);
		Scene::getScene().getCamera().getPosition()=glm::vec3(5*sin(rot),0.0f,5*cos(rot));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDepthMask(GL_FALSE);
		map.Bind();
		map.Draw();
		glDepthMask(GL_TRUE);

		cube.Bind();
		shader.setInt("Texture",2);
		cube.Draw();
		
		floor.Bind();
		floor.Draw();
		// shadow.UnBind();
		//
		// // fb.UnBind();
		// // Scene::getScene().AfterFrameBufferRender();
		// shadow.GetTexture().Bind(0);
		// quad.Bind();
		// quad.Draw();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


		{
			ImGui::Begin("Render Stats");
			ImGui::Text("Time: %.3f ms | %.1f FPS", 1000.0f / io.Framerate, io.Framerate);
            ImGui::SliderFloat("speed", &speed, 0.0f, 0.5f);
			ImGui::End();
		}

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}

void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length,
    const GLchar* msg, const void* data)
{
    const char* _source;
    const char* _type;
    const char* _severity;

    switch (source) {
    case GL_DEBUG_SOURCE_API:
        _source = "API";
        break;

    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        _source = "WINDOW SYSTEM";
        break;

    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        _source = "SHADER COMPILER";
        break;

    case GL_DEBUG_SOURCE_THIRD_PARTY:
        _source = "THIRD PARTY";
        break;

    case GL_DEBUG_SOURCE_APPLICATION:
        _source = "APPLICATION";
        break;

    case GL_DEBUG_SOURCE_OTHER:
        _source = "UNKNOWN";
        break;

    default:
        _source = "UNKNOWN";
        break;
    }

    switch (type) {
    case GL_DEBUG_TYPE_ERROR:
        _type = "ERROR";
        break;

    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        _type = "DEPRECATED BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        _type = "UDEFINED BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_PORTABILITY:
        _type = "PORTABILITY";
        break;

    case GL_DEBUG_TYPE_PERFORMANCE:
        _type = "PERFORMANCE";
        break;

    case GL_DEBUG_TYPE_OTHER:
        _type = "OTHER";
        break;

    case GL_DEBUG_TYPE_MARKER:
        _type = "MARKER";
        break;

    default:
        _type = "UNKNOWN";
        break;
    }

	int _exit=0;
    switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:
        _severity = "HIGH";
		_exit=1;
        break;

    case GL_DEBUG_SEVERITY_MEDIUM:
        _severity = "MEDIUM";
        break;

    case GL_DEBUG_SEVERITY_LOW:
        _severity = "LOW";
        break;

    case GL_DEBUG_SEVERITY_NOTIFICATION:
        _severity = "NOTIFICATION";
        break;

    default:
        _severity = "UNKNOWN";
        break;
    }

	if(severity!=GL_DEBUG_SEVERITY_NOTIFICATION)
		printf("%d: %s of %s severity, raised from %s: %s\n", id, _type, _severity, _source, msg);
	if(_exit==1)
	exit(-1);
}
