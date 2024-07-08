#include "lighting.h"
#include "glfw/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/trigonometric.hpp"
#include "utils/camera/camera.h"
#include "utils/common/common.h"
#include "utils/shader/shader.h"

Lighting::Lighting(const std::string& title, int width, int height)
    : width_(width),
      height_(height),
      previous_frame_(0.0f),
      delta_time_(0.0f),
      light_color_{glm::vec3(1.0f, 1.0f, 1.0f)}
{
    context_ = utils::CommonFunc::initContext(title, width, height);
    camera_ = utils::Camera::instance();
    cube_shader_ = new utils::Shader("light_or_cube.vert", "just_cube.frag");
    light_shader_ = new utils::Shader("light_or_cube.vert", "just_light.frag");
}

Lighting::~Lighting()
{
    delete cube_shader_;
    delete light_shader_;
    delete camera_;
    glDeleteVertexArrays(1, &cube_vao_);
    glDeleteVertexArrays(1, &light_vao_);
    glDeleteBuffers(1, &vbo_);
}

void Lighting::setMouseCb()
{
    glfwSetCursorPosCallback(context_, [](GLFWwindow* window, double x_pos, double y_pos)
                             { camera_->processMouseMove(window, float(x_pos), float(y_pos)); });
    glfwSetScrollCallback(context_, [](GLFWwindow* window, double x_offset, double y_offset)
                          { camera_->processMouseScroll(window, float(x_offset), float(y_offset)); });
}

void Lighting::run()
{
    utils::CommonFunc::enableZBuffer();
    configAndBindObjects();

    int light_index = 0;
    double loop_start_time = glfwGetTime();
    while (!glfwWindowShouldClose(context_))
    {
        auto current_frame = (float)glfwGetTime();
        auto delta_time_ = current_frame - previous_frame_;
        previous_frame_ = current_frame;

        camera_->processInput(context_, delta_time_);
        utils::CommonFunc::render(true);

        cube_shader_->useShaderProgram();
        cube_shader_->setVec3Uniform("cube_color", 1.0f, 0.5f, 0.31f);
        cube_shader_->setVec3Uniform("light_color", light_color_.x, light_color_.y, light_color_.z);
        glm::mat4 view_mat = camera_->getViewMatrix();
        cube_shader_->setMatrix4fUniform("view_mat", glm::value_ptr(view_mat));

        glm::mat4 projection_mat =
            glm::perspective(glm::radians(camera_->getZoom()), float(width_) / float(height_), 0.1f, 100.0f);
        cube_shader_->setMatrix4fUniform("projection_mat", glm::value_ptr(projection_mat));

        light_index %= cube_size;
        for (int index = 0; index < cube_size; ++index)
        {
            if (index == light_index)
            {
                light_shader_->useShaderProgram();

                light_shader_->setVec3Uniform("light_color", light_color_.x, light_color_.y, light_color_.z);
                light_shader_->setMatrix4fUniform("view_mat", glm::value_ptr(view_mat));
                light_shader_->setMatrix4fUniform("projection_mat", glm::value_ptr(projection_mat));

                glm::mat4 model_mat = glm::mat4(1.0);
                model_mat = glm::translate(model_mat, cubes_positions[index]);
                model_mat = glm::scale(model_mat, glm::vec3(0.2f));
                light_shader_->setMatrix4fUniform("model_mat", glm::value_ptr(model_mat));

                glBindVertexArray(light_vao_);
                glDrawArrays(GL_TRIANGLES, 0, 36);

                continue;
            }

            cube_shader_->useShaderProgram();
            glm::mat4 model_mat = glm::mat4(1.0);
            model_mat = glm::translate(model_mat, cubes_positions[index]);
            float angle = glfwGetTime() * (index % 3);
            model_mat = glm::rotate(model_mat, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            cube_shader_->setMatrix4fUniform("model_mat", glm::value_ptr(model_mat));

            glBindVertexArray(cube_vao_);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        if (glfwGetTime() - loop_start_time > color_change_duration_)
        {
            light_index++;
            loop_start_time = glfwGetTime();
            light_color_ = glm::vec3(glm::cos(loop_start_time), glm::sin(loop_start_time), glm::tan(loop_start_time));
        }

        glfwSwapBuffers(context_);
        glfwPollEvents();
    }

    glfwTerminate();
}

void Lighting::configAndBindObjects()
{
    glGenVertexArrays(1, &cube_vao_);
    glBindVertexArray(cube_vao_);

    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glGenVertexArrays(1, &light_vao_);
    glBindVertexArray(light_vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
}