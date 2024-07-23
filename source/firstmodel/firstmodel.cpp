#include "firstmodel.h"
#include "glfw/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/matrix.hpp"
#include "glm/trigonometric.hpp"
#include "utils/camera/camera.h"
#include "utils/common/common.h"
#include "utils/model/model.h"
#include "utils/shader/shader.h"

FirstMode::FirstMode(const std::string& title, int width, int height)
    : width_(width), height_(height), light_color_(glm::vec3(1.0f)), previous_frame_(0.0f), delta_time_(0.0f)
{
    context_ = utils::CommonFunc::initContext(title, width, height);
    camera_ = utils::Camera::instance();

    light_shader_ = new utils::Shader("light_or_cube.vert", "just_light.frag");
    model_shader_ = new utils::Shader("firstmodel.vert", "firstmodel.frag");

    model_ = new utils::Model("nanosuit");
}

FirstMode::~FirstMode()
{
    delete light_shader_;
    delete model_shader_;
    delete camera_;
    glDeleteBuffers(1, &vbo_);
    glDeleteVertexArrays(1, &woodenbox_vao_);
    glDeleteVertexArrays(1, &light_vao_);
}

void FirstMode::setMouseCb()
{
    glfwSetCursorPosCallback(context_, [](GLFWwindow* window, double x_pos, double y_pos)
                             { camera_->processMouseMove(window, (float)x_pos, (float)y_pos); });
    glfwSetScrollCallback(context_, [](GLFWwindow* window, double x_offset, double y_offset)
                          { camera_->processMouseScroll(window, (float)x_offset, (float)y_offset); });
}

void FirstMode::run()
{
    utils::CommonFunc::enableZBuffer();

    while (!glfwWindowShouldClose(context_))
    {
        auto current_frame = (float)glfwGetTime();
        auto delta_time_ = current_frame - previous_frame_;
        previous_frame_ = current_frame;

        utils::CommonFunc::render(true);
        camera_->processInput(context_, delta_time_);

        setupModelShader();
        setupLightShader();

        glfwSwapBuffers(context_);
        glfwPollEvents();
    }
    glfwTerminate();
}

void FirstMode::setupModelShader()
{
    glm::mat4 projection =
        glm::perspective(glm::radians(camera_->getZoom()), float(width_) / float(height_), 0.1f, 100.0f);
    glm::mat4 view = camera_->getViewMatrix();

    model_shader_->useShaderProgram();

    model_shader_->setMatrix4fUniform("projection", glm::value_ptr(projection));
    model_shader_->setMatrix4fUniform("view", glm::value_ptr(view));
    glm::mat4 model = glm::mat4(1.0f);
    model_shader_->setMatrix4fUniform("model", glm::value_ptr((model)));

    model_->drawModel(*model_shader_);
}

void FirstMode::setupLightShader()
{
    glm::mat4 projection =
        glm::perspective(glm::radians(camera_->getZoom()), float(width_) / float(height_), 0.1f, 100.0f);
    glm::mat4 view = camera_->getViewMatrix();

    light_shader_->useShaderProgram();
    light_shader_->setVec3Uniform("light_color", glm::value_ptr(light_color_));
    light_shader_->setMatrix4fUniform("projection_mat", glm::value_ptr(projection));
    light_shader_->setMatrix4fUniform("view_mat", glm::value_ptr(view));
    light_shader_->setMatrix4fUniform("model_mat", glm::value_ptr(lightPosition));

    glBindVertexArray(light_vao_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
