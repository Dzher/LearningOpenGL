#include "materialcube.h"

int main()
{
    MaterialCube light("Phong Lighting", 800, 600);

    light.setMouseCb();
    light.run();

    return 0;
}
