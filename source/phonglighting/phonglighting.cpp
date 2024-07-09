#include "phonglighting.h"
#include "glfw/glfw3.h"
#include "utils/camera/camera.h"
#include "utils/common/common.h"
#include "utils/shader/shader.h"

PhongLight::PhongLight(const std::string& title, int width, int height)
    : width_(width), height_(height), current_mode_(PhongLightingMode::AmbientLight), light_color_(glm::vec3(1.0f))
{
    context_ = utils::CommonFunc::initContext(title, width, height);
    camera_ = utils::Camera::instance();
    cube_shader_ = new utils::Shader("", "");
    light_shader_ = new utils::Shader("", "");
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

void PhongLight::setupCubeShader() {}

void PhongLight::setupLightShader() {}