#include "skybox.h"

int main()
{
    SkyBox skybox = SkyBox("Blending", 800, 600);

    skybox.dropOrBlend(true);
    skybox.setMouseCb();
    skybox.run();

    return 0;
}