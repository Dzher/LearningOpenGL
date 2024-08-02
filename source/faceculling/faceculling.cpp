#include "faceculling.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glfw/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "glm/trigonometric.hpp"
#include "utils/camera/camera.h"
#include "utils/common/common.h"
#include "utils/shader/shader.h"

FaceCull::FaceCull(const std::string& title, unsigned int width, unsigned int height)
    : width_(width), height_(height), previous_frame_(0.f), delta_time_(0.f), cull_(true), face_(CullFace::Back)
{
    context_ = utils::CommonFunc::initContext(title, width, height);
    camera_ = utils::Camera::instance();
    camera_->setPosition(0.f, 0.f, 2.f);

    utils::CommonFunc::configAndBindTexture(texture_wooden_, "woodbox.png");

    shader_ = new utils::Shader("3dbox.vert", "3dbox.frag");
}

FaceCull::~FaceCull()
{
    delete camera_;
    delete shader_;
}

void FaceCull::setMouseCb()
{
    glfwSetCursorPosCallback(context_, [](GLFWwindow* window, double x_pos, double y_pos)
                             { camera_->processMouseMove(window, (float)x_pos, (float)y_pos); });
    glfwSetScrollCallback(context_, [](GLFWwindow* window, double x_offset, double y_offset)
                          { camera_->processMouseScroll(window, (float)x_offset, (float)y_offset); });
}

void FaceCull::cull(bool blend)
{
    cull_ = blend;
}

void FaceCull::setCullFace(CullFace face)
{
    face_ = face;
}

void FaceCull::run()
{
    glEnable(GL_DEPTH_TEST);

    if (cull_)
    {
        glEnable(GL_CULL_FACE);
        if (face_ == CullFace::Back)
        {
            glCullFace(GL_BACK);
        }
        else if (face_ == CullFace::Front)
        {
            glCullFace(GL_FRONT);
        }
        else
        {
            glCullFace(GL_FRONT_AND_BACK);
        }
    }
    drawCube();
}

void FaceCull::drawCube()
{
    glGenVertexArrays(1, &cube_vao_);
    glBindVertexArray(cube_vao_);
    glGenBuffers(1, &cube_vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, cube_vbo_);

    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    glBindVertexArray(0);

    shader_->useShaderProgram();
    shader_->setIntUniform("texture_0", 0);

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
        glm::mat4 model = glm::mat4(1.f);

        shader_->useShaderProgram();
        shader_->setMatrix4fUniform("projection_mat", projection);
        shader_->setMatrix4fUniform("view_mat", view);
        shader_->setMatrix4fUniform("model_mat", model);

        glActiveTexture(texture_wooden_);
        glBindTexture(GL_TEXTURE_2D, texture_wooden_);
        glBindVertexArray(cube_vao_);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(context_);
        glfwPollEvents();
    }
    glfwTerminate();
}
