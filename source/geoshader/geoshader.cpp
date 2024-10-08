#include "geoshader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include "glfw/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"
#include "utils/camera/camera.h"
#include "utils/common/common.h"
#include "utils/model/model.h"
#include "utils/shader/shader.h"

GeoShader::GeoShader(const std::string& title, unsigned int width, unsigned int height)
    : width_(width), height_(height), previous_frame_(0.f), delta_time_(0.f), draw_type_(GeoType::House)
{
    context_ = utils::CommonFunc::initContext(title, width, height);
    camera_ = utils::Camera::instance();
    camera_->setPosition(0.f, 0.f, 10.f);
}

GeoShader::~GeoShader()
{
    delete camera_;
    delete shader_;
}

void GeoShader::setMouseCb()
{
    glfwSetCursorPosCallback(context_, [](GLFWwindow* window, double x_pos, double y_pos)
                             { camera_->processMouseMove(window, (float)x_pos, (float)y_pos); });
    glfwSetScrollCallback(context_, [](GLFWwindow* window, double x_offset, double y_offset)
                          { camera_->processMouseScroll(window, (float)x_offset, (float)y_offset); });
}

void GeoShader::setDrawType(GeoType type)
{
    draw_type_ = type;
}

void GeoShader::run()
{
    glEnable(GL_DEPTH_TEST);

    switch (draw_type_)
    {
        case GeoShader::GeoType::House:
            drawHouse();
            break;
        case GeoShader::GeoType::Boom:
            drawBoom();
            break;
        case GeoShader::GeoType::Normal:
            drawNormal();
            break;
    }
}

void GeoShader::drawHouse()
{
    shader_ = new utils::Shader("geo_house.vert", "geo_house.geom", "geo_house.frag");

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(kHousePoints), kHousePoints, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(context_))
    {
        float current_frame = glfwGetTime();
        delta_time_ = current_frame - previous_frame_;
        previous_frame_ = current_frame;

        camera_->processInput(context_, delta_time_);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vao_);

        shader_->useShaderProgram();
        glDrawArrays(GL_POINTS, 0, 4);

        glfwSwapBuffers(context_);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
    glfwTerminate();
}

void GeoShader::drawBoom()
{
    shader_ = new utils::Shader("geo_boom.vert", "geo_boom.geom", "geo_boom.frag");
    model_ = new utils::Model("nanosuit");

    while (!glfwWindowShouldClose(context_))
    {
        float current_frame = glfwGetTime();
        delta_time_ = current_frame - previous_frame_;
        previous_frame_ = current_frame;

        camera_->processInput(context_, delta_time_);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width_ / (float)height_, 1.0f, 100.0f);
        glm::mat4 view = camera_->getViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);

        shader_->useShaderProgram();
        shader_->setMatrix4fUniform("projection", projection);
        shader_->setMatrix4fUniform("view", view);
        shader_->setMatrix4fUniform("model", model);
        shader_->setFloatUniform("time", current_frame);

        model_->drawModel(*shader_);

        glfwSwapBuffers(context_);
        glfwPollEvents();
    }

    glfwTerminate();
}

void GeoShader::drawNormal()
{
    shader_ = new utils::Shader("firstmodel.vert", "firstmodel.frag");
    auto normal_shader = new utils::Shader("geo_normal.vert", "geo_normal.geom", "geo_normal.frag");
    model_ = new utils::Model("backpack");

    while (!glfwWindowShouldClose(context_))
    {
        float current_frame = glfwGetTime();
        delta_time_ = current_frame - previous_frame_;
        previous_frame_ = current_frame;

        camera_->processInput(context_, delta_time_);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width_ / (float)height_, 1.0f, 100.0f);
        glm::mat4 view = camera_->getViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);

        shader_->useShaderProgram();
        shader_->setMatrix4fUniform("projection", projection);
        shader_->setMatrix4fUniform("view", view);
        shader_->setMatrix4fUniform("model", model);

        model_->drawModel(*shader_);

        normal_shader->useShaderProgram();
        normal_shader->setMatrix4fUniform("projection", projection);
        normal_shader->setMatrix4fUniform("view", view);
        normal_shader->setMatrix4fUniform("model", model);

        model_->drawModel(*normal_shader);

        glfwSwapBuffers(context_);
        glfwPollEvents();
    }

    glfwTerminate();
    delete normal_shader;
}