#include "cameraview.h"
#include "glfw/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "utils/camera/camera.h"
#include "utils/common/common.h"
#include "utils/shader/shader.h"

CameraView::CameraView(const std::string& title, int width, int height)
    : width_(width),
      height_(height),
      old_x_pos_(width / 2.0),
      old_y_pos_(height / 2.0),
      previous_frame_(0.0f),
      delta_time_(0.0f)
{
    context_ = utils::CommonFunc::initContext("Camera", width_, height_);
    camera_ = new utils::Camera();
    camera_->setPosition(0.0f, 0.0f, 3.0f);
    shader_program_ = new utils::Shader("3dbox.vert", "3dbox.frag");
}

CameraView::~CameraView()
{
    delete camera_;
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
}

GLFWwindow* CameraView::getContext()
{
    return context_;
}

void CameraView::configAndBindObjects()
{
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CameraView::configAndBindTexture()
{
    utils::CommonFunc::configAndBindTexture(texture_, "girl.jpg");
    utils::CommonFunc::setTextureIndex(shader_program_->getShaderProgramId(), "texture_0", 0);
}

void CameraView::run()
{
    utils::CommonFunc::enableZBuffer();

    configAndBindObjects();
    configAndBindTexture();

    while (!glfwWindowShouldClose(context_))
    {
        float current_frame = (float)glfwGetTime();
        delta_time_ = current_frame - previous_frame_;
        previous_frame_ = current_frame;

        utils::CommonFunc::processInput(context_, camera_, delta_time_);
        utils::CommonFunc::render(true);

        utils::CommonFunc::activeTexture(texture_);

        shader_program_->useShaderProgram();

        glm::mat4 projection_mat =
            glm::perspective(glm::radians(camera_->getZoom()), float(width_) / float(height_), 0.1f, 100.0f);
        shader_program_->setMatrix4fUniform("projection_mat", glm::value_ptr(projection_mat));

        glm::mat4 view_mat = camera_->getViewMatrix();
        shader_program_->setMatrix4fUniform("view_mat", glm::value_ptr(view_mat));

        glBindVertexArray(vao_);
        for (int cube_index = 0; cube_index < cube_size; ++cube_index)
        {
            glm::mat4 model_mat = glm::mat4(1.0f);
            model_mat = glm::translate(model_mat, cubes_positions[cube_index]);
            float angle = float(glfwGetTime()) * (cube_index % 3 + 1);
            model_mat = glm::rotate(model_mat, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            shader_program_->setMatrix4fUniform("model_mat", glm::value_ptr(model_mat));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(context_);
        glfwPollEvents();
    }
}

void CameraView::mouseMoveCb(GLFWwindow* window, float x_pos, float y_pos)
{
    if (camera_ == nullptr)
    {
        return;
    }

    auto x_offset = old_x_pos_ - x_pos;
    auto y_offset = y_pos - old_y_pos_;
    camera_->processMouseMove(x_offset, y_offset);
    old_x_pos_ = x_pos;
    old_y_pos_ = y_pos;
}

void CameraView::mouseScrollCb(GLFWwindow* window, [[maybe_unused]] float x_offset, float y_offset)
{
    if (camera_ == nullptr)
    {
        return;
    }

    camera_->processMouseScroll(y_offset);
}