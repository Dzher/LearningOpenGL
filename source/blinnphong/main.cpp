#include "blinnphong.h"

int main()
{
    BlinnHhong light("Blinn-Phong Lighting", 800, 600);

    light.setMouseCb();
    light.run();

    return 0;
}
