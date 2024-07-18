#include "woodenbox.h"
#include "glfw/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/matrix.hpp"
#include "glm/trigonometric.hpp"
#include "utils/camera/camera.h"
#include "utils/common/common.h"
#include "utils/shader/shader.h"

WoodenBox::WoodenBox(const std::string& title, int width, int height)
    : width_(width), height_(height), light_color_(glm::vec3(1.0f)), previous_frame_(0.0f), delta_time_(0.0f)
{
    context_ = utils::CommonFunc::initContext(title, width, height);
    camera_ = utils::Camera::instance();

    light_shader_ = new utils::Shader("light_or_cube.vert", "just_light.frag");
    woodenbox_shader_ = new utils::Shader("woodenbox.vert", "woodenbox.frag");

    utils::CommonFunc::configAndBindTexture(diffuse_texture_, "woodbox.png");
    utils::CommonFunc::setTextureIndex(woodenbox_shader_->getShaderProgramId(), "box.diffuse_texture", 0);
    utils::CommonFunc::configAndBindTexture(specular_texture_, "woodboxspecular.png");
    utils::CommonFunc::setTextureIndex(woodenbox_shader_->getShaderProgramId(), "box.specular_texture", 1);

    configAndBindObjects();
}

WoodenBox::~WoodenBox()
{
    delete light_shader_;
    delete woodenbox_shader_;
    delete camera_;
    glDeleteBuffers(1, &vbo_);
    glDeleteVertexArrays(1, &woodenbox_vao_);
    glDeleteVertexArrays(1, &light_vao_);
}

void WoodenBox::setMouseCb()
{
    glfwSetCursorPosCallback(context_, [](GLFWwindow* window, double x_pos, double y_pos)
                             { camera_->processMouseMove(window, (float)x_pos, (float)y_pos); });
    glfwSetScrollCallback(context_, [](GLFWwindow* window, double x_offset, double y_offset)
                          { camera_->processMouseScroll(window, (float)x_offset, (float)y_offset); });
}

void WoodenBox::run()
{
    utils::CommonFunc::enableZBuffer();

    while (!glfwWindowShouldClose(context_))
    {
        auto current_frame = (float)glfwGetTime();
        auto delta_time_ = current_frame - previous_frame_;
        previous_frame_ = current_frame;

        utils::CommonFunc::render(true);
        camera_->processInput(context_, delta_time_);

        setupBoxShader();
        setupLightShader();

        glfwSwapBuffers(context_);
        glfwPollEvents();
    }
    glfwTerminate();
}

void WoodenBox::configAndBindObjects()
{
    glGenVertexArrays(1, &woodenbox_vao_);
    glBindVertexArray(woodenbox_vao_);

    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glGenVertexArrays(1, &light_vao_);
    glBindVertexArray(light_vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
}

void WoodenBox::setupBoxShader()
{
    glm::mat4 projection =
        glm::perspective(glm::radians(camera_->getZoom()), float(width_) / float(height_), 0.1f, 100.0f);
    glm::mat4 view = camera_->getViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);

    woodenbox_shader_->useShaderProgram();
    woodenbox_shader_->setMatrix4fUniform("projection", glm::value_ptr(projection));
    woodenbox_shader_->setMatrix4fUniform("view", glm::value_ptr(view));
    woodenbox_shader_->setMatrix4fUniform("model", glm::value_ptr(model));

    woodenbox_shader_->setVec3Uniform("light.position", glm::value_ptr(light_position_));
    woodenbox_shader_->setVec3Uniform("light.ambient", 0.2f, 0.2f, 0.2f);
    woodenbox_shader_->setVec3Uniform("light.diffuse", 0.5f, 0.5f, 0.5f);
    woodenbox_shader_->setVec3Uniform("light.specular", 1.0f, 1.0f, 1.0f);

    woodenbox_shader_->setVec3Uniform("view_pos", glm::value_ptr(camera_->getPosition()));
    woodenbox_shader_->setFloatUniform("box.shininess", 64.0f);

    utils::CommonFunc::activeTexture(diffuse_texture_, GL_TEXTURE0);
    utils::CommonFunc::activeTexture(specular_texture_, GL_TEXTURE1);

    glBindVertexArray(woodenbox_vao_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void WoodenBox::setupLightShader()
{
    glm::mat4 projection =
        glm::perspective(glm::radians(camera_->getZoom()), float(width_) / float(height_), 0.1f, 100.0f);
    glm::mat4 view = camera_->getViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, light_position_);
    model = glm::scale(model, glm::vec3(0.2f));

    light_shader_->useShaderProgram();
    light_shader_->setVec3Uniform("light_color", glm::value_ptr(light_color_));
    light_shader_->setMatrix4fUniform("project_mat", glm::value_ptr(projection));
    light_shader_->setMatrix4fUniform("view_mat", glm::value_ptr(view));
    light_shader_->setMatrix4fUniform("model_mat", glm::value_ptr(model));

    glBindVertexArray(light_vao_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}