#ifndef __UTILS_CAMERA_H__
#define __UTILS_CAMERA_H__

#include "glad/glad.h"
#include "glfw/glfw3.h"
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
    Camera(const Camera&) = delete;
    Camera(Camera&&) = delete;
    Camera& operator=(const Camera&) = delete;
    Camera& operator=(Camera&&) = delete;

    static Camera* instance();

    void setPosition(float x, float y, float z);

    void setMoveSpeed(float speed);
    void setMouseSensitive(float sensitive);
    void setZoom(float zoom);

    void setYaw(float angle);
    void setPitch(float angle);

    void setConstrainPitch(bool constrain);

    [[nodiscard]] glm::mat4 getViewMatrix();
    [[nodiscard]] float getZoom();
    [[nodiscard]] glm::vec3 getPosition();

    void processKeyboard(CameraDirect direct, float delta_time);
    void processMouseMove(GLFWwindow* window, float x_pos, float y_pos);
    void processMouseScroll(GLFWwindow* window, float x_offset, float y_offset);
    void processInput(GLFWwindow* window, float delta_time = 0);

private:
    explicit Camera();
    void updateCameraVectors();

private:
    inline static Camera* camera_ = nullptr;
    glm::vec3 current_camera_position_;
    glm::vec3 previous_camera_position_;
    glm::vec3 camera_front_;
    glm::vec3 camera_right_;
    glm::vec3 camera_up_;
    glm::vec3 world_up_;

    float move_speed_;
    float mouse_sensitive_;
    float zoom_;

    float pitch_angle_;
    float yaw_angle_;

    bool constrain_pitch_;

    static constexpr float kYawAngle = -90.0f;
    static constexpr float kPitchAngle = 0.0f;
    static constexpr float kMoveSpeed = 2.5f;
    static constexpr float kMouseSensitive = 0.1f;
    static constexpr float kZoom = 45.0f;
};
}  // namespace utils

#endif