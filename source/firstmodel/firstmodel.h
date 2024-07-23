#include <string>
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "glm/glm.hpp"

namespace utils
{
class Camera;
class Shader;
class Model;
}  // namespace utils

class FirstMode
{
public:
    FirstMode(const std::string& title, int width, int height);
    ~FirstMode();

    void setMouseCb();
    void run();

private:
    void setupModelShader();
    void setupLightShader();

private:
    GLFWwindow* context_;
    inline static utils::Camera* camera_;
    utils::Shader* model_shader_;
    utils::Shader* light_shader_;
    utils::Model* model_;

    int width_;
    int height_;

    glm::vec3 light_color_;
    float previous_frame_;
    float delta_time_;

    GLuint woodenbox_vao_;
    GLuint light_vao_;
    GLuint vbo_;

    static constexpr glm::vec3 lightPosition = {1.2f, 1.0f, 2.0f};
    static constexpr glm::vec3 lightDirection = {-0.2f, 1.0f, -0.3f};
};