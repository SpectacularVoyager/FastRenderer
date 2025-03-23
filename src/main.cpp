#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Buffer/Buffer.h"
#include "Textures/Texture.h"

#include "Global/Scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	
	ShaderProgram program("res/shaders/vert.glsl","res/shaders/frag.glsl");

	VertexLayout layout;
	layout.AddEntry(GL_FLOAT,sizeof(float),3);
	layout.AddEntry(GL_FLOAT,sizeof(float),2);
	layout.Bind();

	program.compile();
	Texture texture(GL_TEXTURE_2D, "res/images/brick.jpg",GL_RGB,GL_RGB,3);
	//Texture texture(GL_TEXTURE_2D, "res/images/icon.png",GL_RGBA,GL_RGBA,4);
	texture.Bind();
	texture.Texture2D();


    while (!glfwWindowShouldClose(window))
    {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		processInput(window);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 


		program.setMat4f("model",model);
		Scene::getScene().setGlobalUniforms(program);

        glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

