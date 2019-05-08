// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}


// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 5 ); 
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;

const float PI = 3.1415926f;

void computeMatricesFromInputs(){
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = (float)(currentTime - lastTime);
    lastTime = currentTime;

    struct CursorPos
    {
        double x,y;
        CursorPos operator-(const CursorPos& rhs) const
        {
            CursorPos result;
            result.x = this->x - rhs.x;
            result.y = this->y - rhs.y;
            return result;
        }
        static CursorPos GetCursorPos() {
            CursorPos pos;
            glfwGetCursorPos(window, &pos.x, &pos.y);
            return pos;
        }
    };

    static CursorPos lastCursorPos = CursorPos::GetCursorPos();

    CursorPos cursorPos;
    glfwGetCursorPos(window, &cursorPos.x, &cursorPos.y);

    CursorPos deltaPos = lastCursorPos - cursorPos;
    lastCursorPos = cursorPos;

    horizontalAngle += mouseSpeed * (float)deltaPos.x;
    verticalAngle += mouseSpeed * (float)deltaPos.y;

    glm::vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    double rightAngle = horizontalAngle - PI / 2.0f;
    glm::vec3 right(
        sin(rightAngle),
        0,
        cos(rightAngle)
    );

    glm::vec3 up = glm::cross(right, direction);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        position += direction * speed * deltaTime;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        position -= direction * speed * deltaTime;
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        position += right * speed * deltaTime;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        position -= right * speed * deltaTime;
    }

    ViewMatrix = glm::lookAt(
        position,
        position + direction,
        up
    );

    /* ProjectionMatrix = glm::perspective(glm::radians(initialFoV), 4.0f/3.0f, 0.1f, 100.0f); */
    ProjectionMatrix = glm::perspective(initialFoV, 4.0f/3.0f, 0.1f, 100.0f);
}
