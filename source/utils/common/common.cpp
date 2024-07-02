#include "common.h"

using namespace Utils;

void CommonFunc::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void CommonFunc::frameBufferSizeCb(GLFWwindow* window, GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
}

void CommonFunc::processInput(GLFWwindow* window)
{
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void CommonFunc::render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 0.3f);
    glClear(GL_COLOR_BUFFER_BIT);
}
