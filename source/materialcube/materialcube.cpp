#include "materialcube.h"
#include "glfw/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"
#include "utils/camera/camera.h"
#include "utils/common/common.h"
#include "utils/material/material.h"
#include "utils/shader/shader.h"

MaterialCube::MaterialCube(const std::string& title, int width, int height)
    : width_(width), height_(height), light_color_(glm::vec3(1.0f)), previous_frame_(0.0f), delta_time_(0.0f)
{
    context_ = utils::CommonFunc::initContext(title, width, height);
    glfwSetInputMode(context_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    camera_ = utils::Camera::instance();
    cube_shader_ = new utils::Shader("material.vert", "material.frag");
    light_shader_ = new utils::Shader("light_or_cube.vert", "just_light.frag");
    configAndBindObjects();
}

MaterialCube::~MaterialCube()
{
    delete camera_;
    delete cube_shader_;
    delete light_shader_;
    glDeleteVertexArrays(1, &light_vao_);
    glDeleteVertexArrays(1, &cube_vao_);
    glDeleteBuffers(1, &vbo_);
}

void MaterialCube::setMouseCb()
{
    glfwSetCursorPosCallback(context_, [](GLFWwindow* window, double x_pos, double y_pos)
                             { camera_->processMouseMove(window, float(x_pos), float(y_pos)); });
    glfwSetScrollCallback(context_, [](GLFWwindow* window, double x_offset, double y_offset)
                          { camera_->processMouseScroll(window, float(x_offset), float(y_offset)); });
}

void MaterialCube::run()
{
    utils::CommonFunc::enableZBuffer();
    while (!glfwWindowShouldClose(context_))
    {
        auto current_frame = (float)glfwGetTime();
        auto delta_time_ = current_frame - previous_frame_;
        previous_frame_ = current_frame;

        utils::CommonFunc::render(true);
        camera_->processInput(context_, delta_time_);

        setupCubeShader();
        setupLightShader();

        glfwSwapBuffers(context_);
        glfwPollEvents();
    }
    glfwTerminate();
}

void MaterialCube::configAndBindObjects()
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

void MaterialCube::setupCubeShader()
{
    glm::mat4 projection_mat =
        glm::perspective(glm::radians(camera_->getZoom()), float(width_) / float(height_), 0.1f, 100.f);
    glm::mat4 view_mat = camera_->getViewMatrix();
    glm::mat4 model_mat = glm::mat4(1.0f);

    utils::MaterialFactory* the_cube = new utils::MaterialFactory(utils::KindsOfMaterial::pearl);

    cube_shader_->useShaderProgram();
    cube_shader_->setVec3Uniform("view_position", glm::value_ptr(camera_->getPosition()));

    cube_shader_->setVec3Uniform("light_strength.position", glm::value_ptr(light_position_));
    cube_shader_->setVec3Uniform("light_strength.ambient_strength", .2, .2, .2);
    cube_shader_->setVec3Uniform("light_strength.diffuse_strength", .2, .3, .4);
    cube_shader_->setVec3Uniform("light_strength.specular_strength", 1.0, 1.0, 1.0);

    cube_shader_->setVec3Uniform("cube_material.ambient", glm::value_ptr(the_cube->getMaterial().ambient_rgb));
    cube_shader_->setVec3Uniform("cube_material.diffuse", glm::value_ptr(the_cube->getMaterial().diffuse_rgb));
    cube_shader_->setVec3Uniform("cube_material.specular", glm::value_ptr(the_cube->getMaterial().specular_rgb));
    cube_shader_->setFloatUniform("cube_material.specular_shininess", the_cube->getMaterial().specular_shininess);

    cube_shader_->setMatrix4fUniform("projection_mat", glm::value_ptr(projection_mat));
    cube_shader_->setMatrix4fUniform("view_mat", glm::value_ptr(view_mat));
    cube_shader_->setMatrix4fUniform("model_mat", glm::value_ptr(model_mat));

    glBindVertexArray(cube_vao_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void MaterialCube::setupLightShader()
{
    glm::mat4 projection_mat =
        glm::perspective(glm::radians(camera_->getZoom()), float(width_) / float(height_), 0.1f, 100.f);
    glm::mat4 view_mat = camera_->getViewMatrix();
    glm::mat4 model_mat = glm::mat4(1.0f);
    model_mat = glm::translate(model_mat, light_position_);

    light_shader_->useShaderProgram();
    light_shader_->setVec3Uniform("light_color", light_color_.x, light_color_.y, light_color_.z);

    light_shader_->setMatrix4fUniform("projection_mat", glm::value_ptr(projection_mat));
    light_shader_->setMatrix4fUniform("view_mat", glm::value_ptr(view_mat));
    light_shader_->setMatrix4fUniform("model_mat", glm::value_ptr(model_mat));

    glBindVertexArray(light_vao_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}