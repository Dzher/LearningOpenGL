#include "blinnphong.h"
#include <cstdint>
#include "glfw/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"
#include "utils/camera/camera.h"
#include "utils/common/common.h"
#include "utils/shader/shader.h"

BlinnHhong::BlinnHhong(const std::string& title, int width, int height)
    : width_(width), height_(height), light_color_(glm::vec3(1.0f)), previous_frame_(0.0f), delta_time_(0.0f)
{
    context_ = utils::CommonFunc::initContext(title, width, height);
    glfwSetInputMode(context_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    camera_ = utils::Camera::instance();
    camera_->setPosition(0.f, 0.f, 3.f);
    shader_ = new utils::Shader("blinn.vert", "blinn.frag");
    utils::CommonFunc::configAndBindTexture(plane_texture_, "woodplane.png");
    configAndBindObjects();
}

BlinnHhong::~BlinnHhong()
{
    delete camera_;
    delete shader_;

    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
}

void BlinnHhong::setMouseCb()
{
    glfwSetCursorPosCallback(context_, [](GLFWwindow* window, double x_pos, double y_pos)
                             { camera_->processMouseMove(window, float(x_pos), float(y_pos)); });
    glfwSetScrollCallback(context_, [](GLFWwindow* window, double x_offset, double y_offset)
                          { camera_->processMouseScroll(window, float(x_offset), float(y_offset)); });
}

void BlinnHhong::run()
{
    utils::CommonFunc::enableZBuffer();
    while (!glfwWindowShouldClose(context_))
    {
        auto current_frame = (float)glfwGetTime();
        auto delta_time_ = current_frame - previous_frame_;
        previous_frame_ = current_frame;

        camera_->processInput(context_, delta_time_);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        setupShader();

        glfwSwapBuffers(context_);
        glfwPollEvents();
    }
    glfwTerminate();
}

void BlinnHhong::configAndBindObjects()
{
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kPlaneVertices), kPlaneVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
}

void BlinnHhong::setupShader()
{
    glm::mat4 projection_mat =
        glm::perspective(glm::radians(camera_->getZoom()), float(width_) / float(height_), 0.1f, 100.f);
    glm::mat4 view_mat = camera_->getViewMatrix();
    glm::mat4 model_mat = glm::mat4(1.0f);

    shader_->useShaderProgram();
    shader_->setMatrix4fUniform("projection", projection_mat);
    shader_->setMatrix4fUniform("view", view_mat);
    shader_->setMatrix4fUniform("model_mat", model_mat);

    // set light uniforms
    shader_->setVec3Uniform("view_pos", camera_->getPosition());
    shader_->setVec3Uniform("light_pos", light_position_);
    shader_->setIntUniform("blinn", true);

    // floor
    glBindVertexArray(vao_);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, plane_texture_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
