#include "camera.h"
#include "glm/ext/matrix_transform.hpp"
#include "glm/geometric.hpp"
#include "glm/trigonometric.hpp"

using namespace utils;

Camera::Camera()
    : camera_position_(0.0f, 0.0f, 0.0f),
      camera_front_(0.0f, 0.0f, -1.0f),
      world_up_(0.0f, 1.0f, 0.0f),
      move_speed_(kMoveSpeed),
      mouse_sensitive_(kMouseSensitive),
      zoom_(kZoom),
      yaw_angle_(kYawAngle),
      pitch_angle_(kPitchAngle)
{
    updateCameraVectors();
}

void Camera::setPosition(float x, float y, float z)
{
    camera_position_ = glm::vec3(x, y, z);
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

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(camera_position_, camera_position_ + camera_front_, camera_up_);
}

float Camera::getZoom()
{
    return zoom_;
}

void Camera::processKeyboard(CameraDirect direct, float delta_time)
{
    float velocity = move_speed_ * delta_time;
    switch (direct)
    {
        case utils::CameraDirect::Backward:
            camera_position_ += camera_front_ * velocity;
            break;
        case utils::CameraDirect::Forward:
            camera_position_ -= camera_front_ * velocity;
            break;
        case utils::CameraDirect::Left:
            camera_position_ -= camera_right_ * velocity;
            break;
        case utils::CameraDirect::Right:
            camera_position_ += camera_right_ * velocity;
            break;
    }
}

void Camera::processMouseMove(float x_offset, float y_offset, GLboolean constrain_pitch)
{
    x_offset *= mouse_sensitive_;
    y_offset *= mouse_sensitive_;

    yaw_angle_ += x_offset;
    pitch_angle_ += y_offset;

    if (constrain_pitch)
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
}

void Camera::processMouseScroll(float offset)
{
    zoom_ -= offset;
    if (zoom_ < 1.0f)
    {
        zoom_ = 1.0f;
    }
    if (zoom_ > 45.0f)
    {
        zoom_ = 45.0f;
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