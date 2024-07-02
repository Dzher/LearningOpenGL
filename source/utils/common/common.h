#ifndef __COMMON_UTILS_H__
#define __COMMON_UTILS_H__

#include <string>
#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace Utils
{
class CommonFunc
{
public:
    static GLFWwindow* initContext(std::string_view title);

    static void frameBufferSizeCb(GLFWwindow* window, GLsizei w, GLsizei h);
    static void processInput(GLFWwindow* window);
    static void render();

    static void configAndBindTexture(GLuint& texture, const std::string& file_name, bool flip = false);
};
}  // namespace Utils

#endif