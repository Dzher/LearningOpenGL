#include "stenciltest.h"
#include <GL/gl.h>
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

StencilTest::StencilTest(const std::string& title, int width, int height)
    : width_(width), height_(height), light_color_(glm::vec3(1.0f)), previous_frame_(0.0f), delta_time_(0.0f)
{
    context_ = utils::CommonFunc::initContext(title, width, height);
    camera_ = utils::Camera::instance();

    floor_shader_ = new utils::Shader("light_or_cube.vert", "just_light.frag");
    box_shader_ = new utils::Shader("allkindslight.vert", "allkindslight.frag");

    utils::CommonFunc::configAndBindTexture(box_texture_, "metal.png");
    utils::CommonFunc::setTextureIndex(box_shader_->getShaderProgramId(), "box.diffuse", 0);
    utils::CommonFunc::configAndBindTexture(floor_texture_, "marble.png");
    utils::CommonFunc::setTextureIndex(box_shader_->getShaderProgramId(), "box.specular", 1);

    configAndBindObjects();
}

StencilTest::~StencilTest()
{
    delete floor_shader_;
    delete box_shader_;
    delete camera_;
    glDeleteBuffers(1, &box_vbo_);
    glDeleteBuffers(1, &floor_vbo_);
    glDeleteVertexArrays(1, &box_vao_);
    glDeleteVertexArrays(1, &floor_vao_);
}

void StencilTest::setMouseCb()
{
    glfwSetCursorPosCallback(context_, [](GLFWwindow* window, double x_pos, double y_pos)
                             { camera_->processMouseMove(window, (float)x_pos, (float)y_pos); });
    glfwSetScrollCallback(context_, [](GLFWwindow* window, double x_offset, double y_offset)
                          { camera_->processMouseScroll(window, (float)x_offset, (float)y_offset); });
}

void StencilTest::run()
{
    utils::CommonFunc::enableZBuffer();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    while (!glfwWindowShouldClose(context_))
    {
        auto current_frame = (float)glfwGetTime();
        auto delta_time_ = current_frame - previous_frame_;
        previous_frame_ = current_frame;

        glClearColor(0.2f, 0.3f, 0.3f, 0.3f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        camera_->processInput(context_, delta_time_);

        setupBoxShader();
        setupFloorShader();

        glfwSwapBuffers(context_);
        glfwPollEvents();
    }
    glfwTerminate();
}

void StencilTest::configAndBindObjects()
{
    glGenVertexArrays(1, &box_vao_);
    glBindVertexArray(box_vao_);
    glGenBuffers(1, &box_vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, box_vbo_);

    glBufferData(GL_ARRAY_BUFFER, sizeof(boxVertices), boxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    glGenVertexArrays(1, &floor_vao_);
    glBindVertexArray(floor_vao_);
    glGenBuffers(1, &floor_vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, floor_vbo_);

    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
}

void StencilTest::setupBoxShader()
{
    glm::mat4 projection =
        glm::perspective(glm::radians(camera_->getZoom()), float(width_) / float(height_), 0.1f, 100.0f);
    glm::mat4 view = camera_->getViewMatrix();

    box_shader_->useShaderProgram();

    box_shader_->setMatrix4fUniform("projection", glm::value_ptr(projection));
    box_shader_->setMatrix4fUniform("view", glm::value_ptr(view));

    box_shader_->setVec3Uniform("light.ambient", 0.2f, 0.2f, 0.2f);
    box_shader_->setVec3Uniform("light.diffuse", 0.5f, 0.5f, 0.5f);
    box_shader_->setVec3Uniform("light.specular", 1.0f, 1.0f, 1.0f);

    box_shader_->setVec3Uniform("view_position", glm::value_ptr(camera_->getPosition()));
    box_shader_->setFloatUniform("box.shininess", 64.0f);

    utils::CommonFunc::activeTexture(box_texture_, GL_TEXTURE0);
    utils::CommonFunc::activeTexture(floor_texture_, GL_TEXTURE1);

    glBindVertexArray(box_vao_);
    glm::mat4 model = glm::mat4(1.0f);
    box_shader_->setMatrix4fUniform("model", glm::value_ptr((model)));
}

void StencilTest::setupFloorShader()
{

    glm::mat4 projection =
        glm::perspective(glm::radians(camera_->getZoom()), float(width_) / float(height_), 0.1f, 100.0f);
    glm::mat4 view = camera_->getViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, lightPosition);
    model = glm::scale(model, glm::vec3(0.2f));

    floor_shader_->useShaderProgram();
    floor_shader_->setVec3Uniform("light_color", glm::value_ptr(light_color_));
    floor_shader_->setMatrix4fUniform("projection_mat", glm::value_ptr(projection));
    floor_shader_->setMatrix4fUniform("view_mat", glm::value_ptr(view));
    floor_shader_->setMatrix4fUniform("model_mat", glm::value_ptr(model));

    glBindVertexArray(floor_vao_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
