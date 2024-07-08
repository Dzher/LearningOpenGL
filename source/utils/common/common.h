#ifndef __COMMON_UTILS_H__
#define __COMMON_UTILS_H__

#include <string>
#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace utils
{
class Camera;
class CommonFunc
{
public:
    static GLFWwindow* initContext(std::string_view title, int width = 800, int height = 600);
    static void enableZBuffer();

    static void frameBufferSizeCb(GLFWwindow* window, GLsizei w, GLsizei h);

    static void render(bool enable_z_buffer = false);

    static void configAndBindTexture(GLuint& texture, const std::string& file_name, bool flip = false);
    static void setTextureIndex(const GLuint& program_id, const std::string& texture, GLuint index);
    static void activeTexture(const GLuint& texture);
};
}  // namespace utils

#endif