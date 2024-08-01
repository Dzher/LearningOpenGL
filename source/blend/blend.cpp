#include "blend.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include "glfw/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"
#include "utils/camera/camera.h"
#include "utils/common/common.h"
#include "utils/shader/shader.h"

Blend::Blend(const std::string& title, unsigned int width, unsigned int height)
    : width_(width), height_(height), previous_frame_(0.f), delta_time_(0.f), blend_(true)
{
    context_ = utils::CommonFunc::initContext(title, width, height);
    camera_ = utils::Camera::instance();
    camera_->setPosition(0.f, 0.f, 10.f);

    utils::CommonFunc::configAndBindTexture(texture_floor_, "metal.png");
    utils::CommonFunc::configAndBindTexture(texture_grass_, "grass.png");
    utils::CommonFunc::configAndBindTexture(texture_window_, "window.png");

    drop_shader_ = new utils::Shader("drop.vert", "drop.frag");
    blend_shader_ = new utils::Shader("blend.vert", "blend.frag");
}

Blend::~Blend()
{
    delete camera_;
    delete drop_shader_;
    delete blend_shader_;
}

void Blend::setMouseCb()
{
    glfwSetCursorPosCallback(context_, [](GLFWwindow* window, double x_pos, double y_pos)
                             { camera_->processMouseMove(window, (float)x_pos, (float)y_pos); });
    glfwSetScrollCallback(context_, [](GLFWwindow* window, double x_offset, double y_offset)
                          { camera_->processMouseScroll(window, (float)x_offset, (float)y_offset); });
}

void Blend::dropOrBlend(bool blend)
{
    blend_ = blend;
}

void Blend::run()
{
    glEnable(GL_DEPTH_TEST);

    glGenVertexArrays(1, &floor_vao_);
    glBindVertexArray(floor_vao_);
    glGenBuffers(1, &floor_vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, floor_vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    glGenVertexArrays(1, &transparent_vao_);
    glBindVertexArray(transparent_vao_);
    glGenBuffers(1, &transparent_vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, transparent_vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

    glBindVertexArray(0);

    if (blend_)
    {
        drawWindowWithBlend();
    }
    else
    {
        drawGrassWithDrop();
    }
}

void Blend::drawGrassWithDrop()
{
    drop_shader_->useShaderProgram();
    drop_shader_->setIntUniform("texture1", 0);

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

        glBindVertexArray(floor_vao_);
        glActiveTexture(texture_floor_);
        glBindTexture(GL_TEXTURE_2D, texture_floor_);
        drop_shader_->useShaderProgram();
        drop_shader_->setMatrix4fUniform("projection", glm::value_ptr(projection));
        drop_shader_->setMatrix4fUniform("view", glm::value_ptr(view));
        drop_shader_->setMatrix4fUniform("model", glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(transparent_vao_);
        glActiveTexture(texture_grass_);
        glBindTexture(GL_TEXTURE_2D, texture_grass_);
        for (auto& each : kPositions)
        {
            model = glm::translate(model, each);
            drop_shader_->setMatrix4fUniform("model", glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        glfwSwapBuffers(context_);
        glfwPollEvents();
    }
    glfwTerminate();
}

void Blend::drawWindowWithBlend()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    blend_shader_->useShaderProgram();
    blend_shader_->setIntUniform("texture1", 0);

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

        std::map<float, glm::vec3> sorted_map;
        for (auto& each_pos : kPositions)
        {
            float distance = glm::length(camera_->getPosition() - each_pos);
            sorted_map[distance] = each_pos;
        }

        glBindVertexArray(floor_vao_);
        glActiveTexture(texture_floor_);
        glBindTexture(GL_TEXTURE_2D, texture_floor_);
        blend_shader_->useShaderProgram();
        blend_shader_->setMatrix4fUniform("projection", glm::value_ptr(projection));
        blend_shader_->setMatrix4fUniform("view", glm::value_ptr(view));
        blend_shader_->setMatrix4fUniform("model", glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindVertexArray(transparent_vao_);
        glActiveTexture(texture_window_);
        glBindTexture(GL_TEXTURE_2D, texture_window_);
        for (auto it = sorted_map.rbegin(); it != sorted_map.rend(); ++it)
        {
            model = glm::translate(model, it->second);
            blend_shader_->setMatrix4fUniform("model", glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        glfwSwapBuffers(context_);
        glfwPollEvents();
    }
    glfwTerminate();
}
