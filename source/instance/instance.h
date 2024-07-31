#include <glad/glad.h>
#include <string>

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

class glInstance
{
public:
    glInstance(const std::string& title, unsigned int width, unsigned int height);
    ~glInstance();

    void setMouseCb();
    void useInstance(bool use);
    void run();

private:
    void configRocks();
    void withInstance();
    void withoutInstance();

private:
    GLFWwindow* context_;
    inline static utils::Camera* camera_;
    utils::Shader* without_instance_shader_;
    utils::Shader* planet_shader_;
    utils::Shader* rock_shader_;
    utils::Model* planet_model_;
    utils::Model* rock_model_;

    glm::mat4* rocks_;
    glm::vec3 planet_position_;
    glm::vec3 planet_scale_;

    unsigned int width_;
    unsigned int height_;
    float previous_frame_;
    float delta_time_;

    unsigned int rock_count_;
    bool use_instance_;
};