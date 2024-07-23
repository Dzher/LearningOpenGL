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

private:
    GLFWwindow* context_;
    inline static utils::Camera* camera_;
    utils::Shader* model_shader_;
    utils::Model* model_;

    int width_;
    int height_;

    glm::vec3 light_color_;
    float previous_frame_;
    float delta_time_;
};