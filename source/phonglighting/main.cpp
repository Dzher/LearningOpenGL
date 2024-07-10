#include "phonglighting.h"

int main()
{
    PhongLight light("Phong Lighting", 800, 600);

    light.setMouseCb();
    light.setLightMode(PhongLightingMode::SpecularLight);

    light.run();

    return 0;
}
