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

enum class CullFace
{
    Front,
    Back,
    All
};

class FaceCull
{
public:
    FaceCull(const std::string& title, unsigned int width, unsigned int height);
    ~FaceCull();

    void setMouseCb();
    void cull(bool cull);
    void setCullFace(CullFace face);
    void run();

private:
    void drawCube();

private:
    GLFWwindow* context_;
    inline static utils::Camera* camera_;
    utils::Shader* shader_;

    unsigned int width_;
    unsigned int height_;
    float previous_frame_;
    float delta_time_;

    GLuint texture_wooden_;

    GLuint cube_vao_;
    GLuint cube_vbo_;

    bool cull_;
    CullFace face_;

    static constexpr float cubeVertices[] = {
        // Back face
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // Bottom-left
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,    // top-right
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,   // bottom-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,    // top-right
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  // bottom-left
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,   // top-left
        // Front face
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // bottom-left
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   // bottom-right
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    // top-right
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,    // top-right
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,   // top-left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // bottom-left
        // Left face
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    // top-right
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // top-left
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // bottom-left
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // bottom-left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   // bottom-right
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    // top-right
                                          // Right face
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,     // top-left
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,   // bottom-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,    // top-right
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,   // bottom-right
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,     // top-left
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,    // bottom-left
        // Bottom face
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // top-right
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,   // top-left
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,    // bottom-left
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,    // bottom-left
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   // bottom-right
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // top-right
        // Top face
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  // top-left
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    // bottom-right
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // top-right
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    // bottom-right
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  // top-left
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f    // bottom-left
    };
};