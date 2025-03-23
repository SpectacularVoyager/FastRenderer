#include <GL/glew.h>
#include <GLFW/glfw3.h>
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

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void processInput(GLFWwindow* window){
	if(glfwGetKey(window,GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window,true);
}

void onResize(GLFWwindow* window,int x,int y){
	Scene::getScene().onResize(x,y);
}
int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
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
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable( GL_BLEND );
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glEnable(GL_MULTISAMPLE);  

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwSetWindowSizeCallback(window, onResize);

	float vertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f , 0.0f,
		-1.0f,  1.0f, 0.0f, 0.0f , 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f , 0.0f,
		1.0f,  1.0f, 0.0f, 1.0f , 1.0f
	};
	unsigned int indices[] = {
		0, 2, 3,
		0, 1, 3
	};  

	VertexArray array;
	array.Bind();

	Buffer vertexBuffer(GL_ARRAY_BUFFER,vertices,sizeof(vertices),GL_STATIC_DRAW);
	vertexBuffer.Bind();

	Buffer indexBuffer(GL_ELEMENT_ARRAY_BUFFER,indices,sizeof(indices),GL_STATIC_DRAW);
	indexBuffer.Bind();

	VertexLayout layout;
	layout.AddEntry(GL_FLOAT,sizeof(float),3);
	layout.AddEntry(GL_FLOAT,sizeof(float),2);
	layout.Bind();
	
	ShaderProgram shader("res/shaders/vert.glsl","res/shaders/frag.glsl");


	shader.compile();
	Texture texture(GL_TEXTURE_2D, "res/images/proto/PNG/Dark/texture_04.png",GL_RGB,GL_RGB,3);
	Texture textureIcon(GL_TEXTURE_2D, "res/images/icon.png",GL_RGBA,GL_RGBA,4);
	texture.Bind();
	texture.Texture2D();


	textureIcon.Bind();
	textureIcon.Texture2D();

	shader.Use();


	Cube cube(shader);
	cube.transform*=glm::scale(glm::mat4(1.0f),glm::vec3(0.5));
	Icon icon(shader,glm::translate(glm::scale(glm::mat4(1.0f),glm::vec3(0.2f)),glm::vec3(0.0f,4.0f,0.0f)));
	Icon icon2(shader,glm::translate(glm::scale(glm::mat4(1.0f),glm::vec3(0.2f)),glm::vec3(0.0f,-4.0f,0.0f)));

    while (!glfwWindowShouldClose(window))
    {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		processInput(window);

		cube.transform=glm::rotate(cube.transform,glm::radians(0.3f),glm::vec3(0.0f,1.0f,0.0f));
		Scene::getScene().setGlobalUniforms(shader);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		texture.Bind();
		cube.Bind();
		cube.Draw();
		//glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
		//Scene::getScene().setGlobalUniforms(shader);
		textureIcon.Bind();
		icon.Bind();
		icon.Draw();

		icon2.Bind();
		icon2.Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

