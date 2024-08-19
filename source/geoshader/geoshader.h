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
class Model;
}  // namespace utils

class GeoShader
{
public:
    enum class GeoType
    {
        House,
        Boom,
        Normal
    };

public:
    GeoShader(const std::string& title, unsigned int width, unsigned int height);
    ~GeoShader();

    void setMouseCb();
    void setDrawType(GeoType type);
    void run();

private:
    void drawHouse();
    void drawBoom();
    void drawNormal();

private:
    GLFWwindow* context_;
    inline static utils::Camera* camera_;
    utils::Shader* shader_;
    utils::Model* model_;

    unsigned int width_;
    unsigned int height_;
    float previous_frame_;
    float delta_time_;

    GLuint vao_;
    GLuint vbo_;

    GeoType draw_type_;

    static constexpr float kHousePoints[] = {
        -0.5f, 0.5f,  1.0f, 0.0f, 0.0f,  // top-left
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  // top-right
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f,  // bottom-right
        -0.5f, -0.5f, 1.0f, 1.0f, 0.0f   // bottom-left
    };
};