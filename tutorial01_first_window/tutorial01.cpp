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

#include <common/shader.hpp>

int main( void )
{
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1024, 768, "First Window", nullptr, nullptr);
    if (!window) {
        fprintf(stderr, "Failed to create window\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    GLfloat vertexData[] = {
        -1.0f, -1.0f, 0.0f, 1.0, 0.0, 0.0,
         1.0f, -1.0f, 0.0f, 0.0, 1.0, 0.0,
         0.0f,  1.0f, 0.0f, 0.0, 0.0, 1.0,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    GLuint programID;
    programID = LoadShaders("Simple.vert", "Simple.frag");

    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

    do {
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(programID);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(GLfloat)*6,
                (const void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1,
                3,
                GL_FLOAT,
                GL_FALSE,
                sizeof(GLfloat)*6,
                (const void*)(sizeof(GLfloat)*3));

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glfwSwapBuffers(window);
        glfwPollEvents();
    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
            glfwWindowShouldClose(window) == 0);

    glDeleteBuffers(1, vertexBuffer);
    glDeleteVertexArray(1, vao);
    glDeleteProgram(programID);

    glfwTerminate();

	return 0;
}

