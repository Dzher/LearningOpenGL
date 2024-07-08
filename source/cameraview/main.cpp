#include "cameraview.h"
#include "glfw/glfw3.h"

int main()
{
    CameraView view("Camera View", 800, 600);
    view.setMouseCb();
    // glfwSetInputMode(view.getContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    view.run();

    glfwTerminate();
    return 0;
}
