#include "camera.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"

using namespace utils;

Camera::Camera()
    : current_camera_position_(0.0f, 0.0f, 0.0f),
      previous_camera_position_(current_camera_position_),
      camera_front_(0.0f, 0.0f, -1.0f),
      world_up_(0.0f, 1.0f, 0.0f),
      move_speed_(kMoveSpeed),
      mouse_sensitive_(kMouseSensitive),
      zoom_(kZoom),
      yaw_angle_(kYawAngle),
      pitch_angle_(kPitchAngle),
      constrain_pitch_(true)
{
    updateCameraVectors();
}

Camera* Camera::instance()
{
    if (camera_ == nullptr)
    {
        camera_ = new Camera();
    }
    return camera_;
}

void Camera::setPosition(float x, float y, float z)
{
    current_camera_position_ = glm::vec3(x, y, z);
}

void Camera::setMoveSpeed(float speed)
{
    move_speed_ = speed;
}

void Camera::setMouseSensitive(float sensitive)
{
    mouse_sensitive_ = sensitive;
}

void Camera::setZoom(float zoom)
{
    zoom_ = zoom;
}

void Camera::setYaw(float angle)
{
    yaw_angle_ = angle;
}

void Camera::setPitch(float angle)
{
    pitch_angle_ = angle;
}

void Camera::setConstrainPitch(bool constrain)
{
    constrain_pitch_ = constrain;
}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(current_camera_position_, current_camera_position_ + camera_front_, camera_up_);
}

float Camera::getZoom()
{
    return zoom_;
}

glm::vec3 Camera::getPosition()
{
    return glm::vec3(current_camera_position_);
}

void Camera::processKeyboard(CameraDirect direct, float delta_time)
{
    float velocity = move_speed_ * delta_time;
    switch (direct)
    {
        case utils::CameraDirect::Backward:
            current_camera_position_ += camera_front_ * velocity;
            break;
        case utils::CameraDirect::Forward:
            current_camera_position_ -= camera_front_ * velocity;
            break;
        case utils::CameraDirect::Left:
            current_camera_position_ -= camera_right_ * velocity;
            break;
        case utils::CameraDirect::Right:
            current_camera_position_ += camera_right_ * velocity;
            break;
    }
}

void Camera::processMouseMove(GLFWwindow* window, float x_pos, float y_pos)
{
    auto x_offset = previous_camera_position_.x - x_pos;
    auto y_offset = y_pos - previous_camera_position_.y;

    x_offset *= mouse_sensitive_;
    y_offset *= mouse_sensitive_;

    yaw_angle_ += x_offset;
    pitch_angle_ += y_offset;

    if (constrain_pitch_)
    {
        if (pitch_angle_ > 89.0f)
        {
            pitch_angle_ = 89.0f;
        }
        if (pitch_angle_ < -89.0f)
        {
            pitch_angle_ = -89.0f;
        }
    }

    updateCameraVectors();

    previous_camera_position_.x = x_pos;
    previous_camera_position_.y = y_pos;
}

void Camera::processMouseScroll(GLFWwindow* window, float x_offset, float y_offset)
{
    zoom_ -= y_offset;
    if (zoom_ < 1.0f)
    {
        zoom_ = 1.0f;
    }
    if (zoom_ > 45.0f)
    {
        zoom_ = 45.0f;
    }
}

void Camera::processInput(GLFWwindow* window, float delta_time)
{
    if (window == nullptr)
    {
        return;
    }

    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (delta_time == 0)
    {
        return;
    }
    if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_W))
    {
        processKeyboard(CameraDirect::Forward, delta_time);
    }
    else if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_A))
    {
        processKeyboard(CameraDirect::Left, delta_time);
    }
    else if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_S))
    {
        processKeyboard(CameraDirect::Backward, delta_time);
    }
    else if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_D))
    {
        processKeyboard(CameraDirect::Right, delta_time);
    }
}

void Camera::updateCameraVectors()
{
    glm::vec3 new_camera_front;
    new_camera_front.x = glm::cos(glm::radians(yaw_angle_)) * glm::cos(glm::radians(pitch_angle_));
    new_camera_front.y = glm::sin(glm::radians(pitch_angle_));
    new_camera_front.z = glm::sin(glm::radians(yaw_angle_)) * glm::cos(glm::radians(pitch_angle_));

    camera_front_ = glm::normalize(new_camera_front);

    camera_right_ = glm::normalize(glm::cross(camera_front_, world_up_));
    camera_up_ = glm::normalize(glm::cross(camera_right_, camera_front_));
}