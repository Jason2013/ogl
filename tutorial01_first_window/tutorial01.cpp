// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

int main( void )
{

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW!");
        getchar();
        return -1;
    }

    glfwWindowInit(GLFW_SAMPLES, 4);
    glfwWindowInit(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowInit(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowInit(GLFW_FORWARD_COMPAT, GL_TRUE);
    glfwWindowInit(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!(window = glfwCreateWindow(800, 600, "First Window", NULL, NULL)))
    {
        fprintf(stderr, "Failed to create the main window!");
        getchar();
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to load GLEW!");
        getchar();
        glfwTerminate();
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

    do
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_ESCAPE_KEY) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0);

    glfwTerminate();

	return 0;
}

