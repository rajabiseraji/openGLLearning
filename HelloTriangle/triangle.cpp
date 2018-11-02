#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const char* vertexShaderSource = "#version 330 core \
layout(location = 0) in vec3 aPos; \
void main() \
{ \
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \
}"; 

const char* fragmentShaderSource = "#version 330 core \
out vec4 FragColor; \
void main() \
{ \
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \
}";

int main() {
	/*
		Because of their parallel nature, graphics cards of
		today have thousands of small processing cores to 
		quickly process your data within the graphics pipeline 
		by running small programs on the GPU for each step of the pipeline. 
		These small programs are called shaders.
		Shaders are written in the OpenGL Shading Language (GLSL)
	*/

	//vertex input, must be normalized (between -1 ,  1) all in NDC
	//Normalized Device Coordinates
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	unsigned int VBO;
	//this is an object initiation
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// From that point on any buffer calls we make (on the GL_ARRAY_BUFFER target) will be used to configure the currently bound buffer, which is VBO.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//now the data is copied in the memory of graphic card

	//compile vertex shader
	//this one stores an ID to the vertexShader object in our State machine
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//compile fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//linking shaders
	//To use the recently compiled shaders we have to link them to a shader program object and then activate this shader program when rendering objects. 
	//this again is an ID to shaderprogram in our state
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	//attach the previously compiled shaders to the shaderPorgram
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);
	//Every shader and rendering call after glUseProgram will now use this program object (and thus the shaders).
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	return 0;
}