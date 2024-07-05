#ifndef __UTILS_CAMERA_H__
#define __UTILS_CAMERA_H__

#include "glad/glad.h"
#include "glm/glm.hpp"

namespace utils
{

enum class CameraDirect
{
    Forward,
    Backward,
    Left,
    Right
};

class Camera
{
public:
    explicit Camera();

    void setPosition(float x, float y, float z);

    void setMoveSpeed(float speed);
    void setMouseSensitive(float sensitive);
    void setZoom(float zoom);

    void setYaw(float angle);
    void setPitch(float angle);

    [[nodiscard]] glm::mat4 getViewMatrix();
    [[nodiscard]] float getZoom();

    void processKeyboard(CameraDirect direct, float delta_time);
    void processMouseMove(float x_offset, float y_offset, GLboolean constrain_pitch = true);
    void processMouseScroll(float offset);

private:
    void updateCameraVectors();

private:
    glm::vec3 camera_position_;
    glm::vec3 camera_front_;
    glm::vec3 camera_right_;
    glm::vec3 camera_up_;
    glm::vec3 world_up_;

    float move_speed_;
    float mouse_sensitive_;
    float zoom_;

    float pitch_angle_;
    float yaw_angle_;

    static constexpr float kYawAngle = -90.0f;
    static constexpr float kPitchAngle = 0.0f;
    static constexpr float kMoveSpeed = 2.5f;
    static constexpr float kMouseSensitive = 0.1f;
    static constexpr float kZoom = 45.0f;
};
}  // namespace utils

#endif