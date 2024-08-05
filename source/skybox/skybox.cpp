#include "skybox.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glfw/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"
#include "utils/camera/camera.h"
#include "utils/common/common.h"
#include "utils/shader/shader.h"

SkyBox::SkyBox(const std::string& title, unsigned int width, unsigned int height)
    : width_(width), height_(height), previous_frame_(0.f), delta_time_(0.f)
{
    context_ = utils::CommonFunc::initContext(title, width, height);
    camera_ = utils::Camera::instance();
    camera_->setPosition(0.f, 0.f, 10.f);

    utils::CommonFunc::configAndBind3DTexture(texture_skybox_, "skybox");
    skybox_shader_ = new utils::Shader("skybox.vert", "skybox.frag");
}

SkyBox::~SkyBox()
{
    delete camera_;
    delete skybox_shader_;
}

void SkyBox::setMouseCb()
{
    glfwSetCursorPosCallback(context_, [](GLFWwindow* window, double x_pos, double y_pos)
                             { camera_->processMouseMove(window, (float)x_pos, (float)y_pos); });
    glfwSetScrollCallback(context_, [](GLFWwindow* window, double x_offset, double y_offset)
                          { camera_->processMouseScroll(window, (float)x_offset, (float)y_offset); });
}

void SkyBox::run()
{
    glEnable(GL_DEPTH_TEST);

    glGenVertexArrays(1, &skybox_vao_);
    glBindVertexArray(skybox_vao_);
    glGenBuffers(1, &skybox_vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, skybox_vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    skybox_shader_->useShaderProgram();
    skybox_shader_->setIntUniform("skybox", 0);

    while (!glfwWindowShouldClose(context_))
    {
        float current_frame = glfwGetTime();
        delta_time_ = current_frame - previous_frame_;
        previous_frame_ = current_frame;

        camera_->processInput(context_, delta_time_);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection =
            glm::perspective(glm::radians(camera_->getZoom()), float(width_) / float(height_), 0.1f, 100.f);
        glm::mat4 view = camera_->getViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);

        // draw skybox as last
        // change depth function so depth test passes when values are equal to depth buffer's content
        glDepthFunc(GL_LEQUAL);
        skybox_shader_->useShaderProgram();
        // remove translation from the view matrix
        view = glm::mat4(glm::mat3(view));
        skybox_shader_->setMatrix4fUniform("projection", projection);
        skybox_shader_->setMatrix4fUniform("view", view);
        // skybox cube
        glBindVertexArray(skybox_vao_);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, texture_skybox_);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);  // set depth function back to default
        
        glfwSwapBuffers(context_);
        glfwPollEvents();
    }
    glfwTerminate();
}
