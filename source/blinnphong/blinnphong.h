#include <string>
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"

namespace utils
{
class Camera;
class Shader;
} // namespace utils

class BlinnHhong
{
public:
    BlinnHhong(const std::string& title, int width, int height);
    ~BlinnHhong();

    void setMouseCb();
    void run();

private:
    void configAndBindObjects();
    void setupShader();

private:
    GLFWwindow* context_;
    inline static utils::Camera* camera_;
    utils::Shader* shader_;

    int width_;
    int height_;

    glm::vec3 light_color_;
    float previous_frame_;
    float delta_time_;

    GLuint vao_;
    GLuint vbo_;
    GLuint plane_texture_;

    static constexpr float kPlaneVertices[] = {
        // clang-format off
        // positions            // normals         // texcoords
         10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

         10.0f, -0.5f,  10.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
         10.0f, -0.5f, -10.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
        // clang-format on
    };
    static constexpr glm::vec3 light_position_ = {0.f, 0.f, 0.f};
};