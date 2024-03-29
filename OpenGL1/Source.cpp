

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {

	// we want to initialize GLAD before we call any OpenGL function


	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//on MAC OSX
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "First OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//GLFW gives us glfwGetProcAddress that defines the correct function based on which OS we're compiling for.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//from now on we can call openGL functions
	glViewport(0, 0, 800, 600);

	//registering resize callback
	//For retina displays width and height will end up significantly higher than the original input values.
	//We register the callback functions after we've created the window and before the game loop is initiated.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//render loop: a while that doesn't let the application to quit before it's explicitly told to
	while (!glfwWindowShouldClose(window)) {
		//makes sure the escape key is not pressed
		//input happens here
		processInput(window);

		//rendering
		// At the start of each render iteration we always want to clear the screen otherwise we would still see the results from the previous iteration (this could be the effect you're looking for, but usually you don't)
		//we also set a color via glClearColor to clear the screen with
		//a state setting function
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//now clear the buffer with mentioned values
		//a state using function
		glClear(GL_COLOR_BUFFER_BIT);


		//reactivity with callbacks
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

