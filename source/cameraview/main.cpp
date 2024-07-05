#include "cameraview.h"
#include "glfw/glfw3.h"

int main()
{
    static CameraView app("Camera", 800, 600);
    auto* context = app.getContext();

    glfwSetCursorPosCallback(context, [](GLFWwindow* window, double x_pos, double y_pos)
                             { app.mouseMoveCb(window, float(x_pos), float(y_pos)); });
    glfwSetScrollCallback(context, [](GLFWwindow* window, double x_offset, double y_offset)
                          { app.mouseMoveCb(window, float(x_offset), float(y_offset)); });
    // glfwSetInputMode(context, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    app.run();

    glfwTerminate();
    return 0;
}
