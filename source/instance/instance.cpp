#include "instance.h"
#include "glfw/glfw3.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "utils/camera/camera.h"
#include "utils/common/common.h"
#include "utils/model/model.h"
#include "utils/shader/shader.h"

glInstance::glInstance(const std::string& title, unsigned int width, unsigned int height)
    : width_(width),
      height_(height),
      planet_position_(glm::vec3(0.f, -4.f, 0.f)),
      planet_scale_(glm::vec3(4.f, 4.f, 4.f)),
      previous_frame_(0.f),
      delta_time_(0.f),
      use_instance_(true),
      rock_count_(0)
{
    context_ = utils::CommonFunc::initContext(title, width, height);
    camera_ = utils::Camera::instance();
    camera_->setPosition(0.f, 0.f, 55.f);
    planet_model_ = new utils::Model("planet");
    rock_model_ = new utils::Model("rock");
}

glInstance::~glInstance()
{
    delete camera_;
    delete without_instance_shader_;
    delete planet_shader_;
    delete rock_shader_;
    delete planet_model_;
    delete rock_model_;
    delete[] rocks_;
}

void glInstance::setMouseCb()
{
    glfwSetCursorPosCallback(context_, [](GLFWwindow* window, double x_pos, double y_pos)
                             { camera_->processMouseMove(window, (float)x_pos, (float)y_pos); });
    glfwSetScrollCallback(context_, [](GLFWwindow* window, double x_offset, double y_offset)
                          { camera_->processMouseScroll(window, (float)x_offset, (float)y_offset); });
}

void glInstance::useInstance(bool use)
{
    use_instance_ = use;
}

void glInstance::run()
{
    glEnable(GL_DEPTH_TEST);
    configRocks();

    if (use_instance_)
    {
        withInstance();
    }
    else
    {
        withoutInstance();
    }
}

void glInstance::withInstance()
{
    planet_shader_ = new utils::Shader("instance_planet.vert", "instance_planet.frag");
    rock_shader_ = new utils::Shader("instance_rock.vert", "instance_rock.frag");
}

void glInstance::withoutInstance()
{
    without_instance_shader_ = new utils::Shader("instance_no.vert", "instance_no.frag");
    while (!glfwWindowShouldClose(context_))
    {
        float current_frame = glfwGetTime();
        delta_time_ = current_frame - previous_frame_;
        previous_frame_ = current_frame;

        camera_->processInput(context_, delta_time_);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection =
            glm::perspective(glm::radians(camera_->getZoom()), float(width_) / float(height_), 0.1f, 1000.f);
        glm::mat4 view = camera_->getViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, planet_position_);
        model = glm::scale(model, planet_scale_);

        without_instance_shader_->useShaderProgram();
        without_instance_shader_->setMatrix4fUniform("projection", glm::value_ptr(projection));
        without_instance_shader_->setMatrix4fUniform("view", glm::value_ptr(view));
        without_instance_shader_->setMatrix4fUniform("model", glm::value_ptr(model));
        planet_model_->drawModel(*without_instance_shader_);

        for (unsigned int index = 0; index < rock_count_; ++index)
        {
            without_instance_shader_->setMatrix4fUniform("model", glm::value_ptr(rocks_[index]));
            rock_model_->drawModel(*without_instance_shader_);
        }

        glfwSwapBuffers(context_);
        glfwPollEvents();
    }
    glfwTerminate();
}

void glInstance::configRocks()
{
    rock_count_ = use_instance_ ? 100000 : 1000;
    float radius = use_instance_ ? 150.0 : 50.f;
    float offset = use_instance_ ? 25.0f : 2.5f;

    rocks_ = new glm::mat4[rock_count_];
    srand(static_cast<unsigned int>(glfwGetTime()));

    for (unsigned int index = 0; index < rock_count_; ++index)
    {
        glm::mat4 model = glm::mat4(1.0f);
        // 1. translation: displace along circle with 'radius' in range [-offset, offset]
        float angle = (float)index / (float)rock_count_ * 360.0f;
        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float x = sin(angle) * radius + displacement;
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float y = displacement * 0.4f;  // keep height of asteroid field smaller compared to width of x and z
        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
        float z = cos(angle) * radius + displacement;
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. scale: Scale between 0.05 and 0.25f
        float scale = static_cast<float>((rand() % 20) / 100.0 + 0.05);
        model = glm::scale(model, glm::vec3(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = static_cast<float>((rand() % 360));
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

        // 4. now add to list of matrices
        rocks_[index] = model;
    }
}