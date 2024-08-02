#include <glad/glad.h>
#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glfw/glfw3.h"
#include "glm/fwd.hpp"

namespace utils
{
class Camera;
class Shader;
}  // namespace utils

class Blend
{
public:
    Blend(const std::string& title, unsigned int width, unsigned int height);
    ~Blend();

    void setMouseCb();
    void dropOrBlend(bool blend);
    void run();

private:
    void drawGrassWithDrop();
    void drawWindowWithBlend();

private:
    GLFWwindow* context_;
    inline static utils::Camera* camera_;
    utils::Shader* drop_shader_;
    utils::Shader* blend_shader_;

    unsigned int width_;
    unsigned int height_;
    float previous_frame_;
    float delta_time_;

    GLuint texture_grass_;
    GLuint texture_window_;
    GLuint texture_floor_;

    GLuint floor_vao_;
    GLuint floor_vbo_;
    GLuint transparent_vao_;
    GLuint transparent_vbo_;

    bool blend_;

    static constexpr float planeVertices[] = {
        // clang-format off
        // positions          // texture Coords 
         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
        // clang-format on
    };
    static constexpr float transparentVertices[] = {
        // clang-format off
        // positions         // texture Coords 
        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

        0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
        1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
        1.0f,  0.5f,  0.0f,  1.0f,  0.0f
        // clang-format on
    };
    std::vector<glm::vec3> kPositions{glm::vec3(-1.5f, 0.0f, -0.48f), glm::vec3(1.5f, 0.0f, 0.51f),
                                      glm::vec3(0.0f, 0.0f, 0.7f), glm::vec3(-0.3f, 0.0f, -2.3f),
                                      glm::vec3(0.5f, 0.0f, -0.6f)};
};