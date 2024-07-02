#ifndef __COMMON_UTILS_H__
#define __COMMON_UTILS_H__

#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace Utils
{
class CommonFunc
{
public:
    static void init();

    static void frameBufferSizeCb(GLFWwindow* window, GLsizei w, GLsizei h);
    static void processInput(GLFWwindow* window);
    static void render();
};
}  // namespace Utils

#endif