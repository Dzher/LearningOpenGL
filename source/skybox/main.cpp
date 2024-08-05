#include "skybox.h"

int main()
{
    SkyBox skybox = SkyBox("Skybox", 800, 600);

    skybox.setMouseCb();
    skybox.run();

    return 0;
}