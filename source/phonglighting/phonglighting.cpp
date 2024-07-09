#include "phonglighting.h"
#include "glfw/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"
#include "utils/camera/camera.h"
#include "utils/common/common.h"
#include "utils/shader/shader.h"

PhongLight::PhongLight(const std::string& title, int width, int height)
    : width_(width), height_(height), current_mode_(PhongLightingMode::AmbientLight), light_color_(glm::vec3(1.0f))
{
    context_ = utils::CommonFunc::initContext(title, width, height);
    camera_ = utils::Camera::instance();
    cube_shader_ = new utils::Shader("phong_cube.vert", "phong_cube.frag");
    light_shader_ = new utils::Shader("light_or_cube.vert", "just_light.frag");
    configAndBindObjects();
}

PhongLight::~PhongLight()
{
    delete camera_;
    delete cube_shader_;
    delete light_shader_;
    glDeleteVertexArrays(1, &light_vao_);
    glDeleteVertexArrays(1, &cube_vao_);
    glDeleteBuffers(1, &vbo_);
}

void PhongLight::setLightMode(PhongLightingMode mode)
{
    current_mode_ = mode;
}

void PhongLight::run()
{
    utils::CommonFunc::enableZBuffer();
    while (!glfwWindowShouldClose(context_))
    {
        utils::CommonFunc::render(true);
        camera_->processInput(context_);

        setupCubeShader();
        setupLightShader();

        glfwSwapBuffers(context_);
        glfwPollEvents();
    }
    glfwTerminate();
}

void PhongLight::configAndBindObjects()
{
    glGenVertexArrays(1, &cube_vao_);
    glBindVertexArray(cube_vao_);

    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glGenVertexArrays(1, &light_vao_);
    glBindVertexArray(light_vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
}

void PhongLight::setupCubeShader()
{
    glm::mat4 projection_mat =
        glm::perspective(glm::radians(camera_->getZoom()), float(width_) / float(height_), 0.1f, 100.f);
    glm::mat4 view_mat = camera_->getViewMatrix();
    glm::mat4 model_mat = glm::mat4(1.0f);

    cube_shader_->useShaderProgram();
    cube_shader_->setVec3Uniform("light_color", 1.0f, 1.0f, 1.0f);
    cube_shader_->setVec3Uniform("object_color", 1.0f, 0.5f, 0.31f);
    cube_shader_->setVec3Uniform("light_position", light_position_.x, light_position_.y, light_position_.z);

    cube_shader_->setMatrix4fUniform("projection_mat", glm::value_ptr(projection_mat));
    cube_shader_->setMatrix4fUniform("view_mat", glm::value_ptr(view_mat));
    cube_shader_->setMatrix4fUniform("model_mat", glm::value_ptr(model_mat));

    glBindVertexArray(cube_vao_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void PhongLight::setupLightShader()
{
    glm::mat4 projection_mat =
        glm::perspective(glm::radians(camera_->getZoom()), float(width_) / float(height_), 0.1f, 100.f);
    glm::mat4 view_mat = camera_->getViewMatrix();
    glm::mat4 model_mat = glm::mat4(1.0f);
    model_mat = glm::translate(model_mat, light_position_);

    light_shader_->useShaderProgram();
    light_shader_->setMatrix4fUniform("projection_mat", glm::value_ptr(projection_mat));
    light_shader_->setMatrix4fUniform("view_mat", glm::value_ptr(view_mat));
    light_shader_->setMatrix4fUniform("model_mat", glm::value_ptr(model_mat));

    glBindVertexArray(light_vao_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}