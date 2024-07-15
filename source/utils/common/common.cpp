#include "common.h"
#include "glfw/glfw3.h"
#include "utils/camera/camera.h"
#include "utils/pathhelper/pathhelper.h"

#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

using namespace utils;

GLFWwindow* CommonFunc::initContext(std::string_view title, int width, int height)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    int monitor_count;
    GLFWmonitor** monitor_list = glfwGetMonitors(&monitor_count);
    GLFWmonitor* the_display_monitor = monitor_count >= 2 ? monitor_list[1] : monitor_list[0];
    if (the_display_monitor == nullptr)
    {
        return nullptr;
    }

    int x_pos, y_pos;
    glfwGetMonitorPos(the_display_monitor, &x_pos, &y_pos);
    const GLFWvidmode* monitor_mode = glfwGetVideoMode(the_display_monitor);
    int monitor_dpi_x = monitor_mode->width;
    int monitor_dpi_y = monitor_mode->height;

    GLFWwindow* window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwSetWindowPos(window, x_pos + (monitor_dpi_x - width) / 2, y_pos + (monitor_dpi_y - height) / 2);
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, frameBufferSizeCb);

    if (auto proc_address = (GLADloadproc)glfwGetProcAddress; !gladLoadGLLoader(proc_address))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }
    return window;
}

void CommonFunc::enableZBuffer()
{
    glEnable(GL_DEPTH_TEST);
}

void CommonFunc::frameBufferSizeCb(GLFWwindow* window, GLsizei w, GLsizei h)
{
    glViewport(0, 0, w, h);
}

void CommonFunc::render(bool enable_z_buffer)
{
    glClearColor(0.2f, 0.3f, 0.3f, 0.3f);
    glClear(GL_COLOR_BUFFER_BIT);
    if (enable_z_buffer)
    {
        glClear(GL_DEPTH_BUFFER_BIT);
    }
}

void CommonFunc::configAndBindTexture(GLuint& texture, const std::string& file_name, bool flip)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(flip);

    int width, height, nrChannels;
    unsigned char* data =
        stbi_load(utils::PathHelper::getImagePath(file_name).c_str(), &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void CommonFunc::setTextureIndex(const GLuint& program_id, const std::string& name, GLuint index)
{
    glUseProgram(program_id);
    glUniform1i(glGetUniformLocation(program_id, name.data()), index);
}

void CommonFunc::activeTexture(const GLuint& texture, GLenum index)
{
    glActiveTexture(index);
    glBindTexture(GL_TEXTURE_2D, texture);
}