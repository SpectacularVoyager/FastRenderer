#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shaders/ShaderProgram.h"
#include "Buffer/Buffer.h"
#include "Textures/Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void processInput(GLFWwindow* window){
	if(glfwGetKey(window,GLFW_KEY_ESCAPE))
		glfwSetWindowShouldClose(window,true);
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
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
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
	Texture texture(GL_TEXTURE_2D, "res/images/icon.png",GL_RGBA,GL_RGBA,4);
	texture.Bind();
	texture.Texture2D();


    while (!glfwWindowShouldClose(window))
    {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

