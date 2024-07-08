#include "lighting.h"

int main()
{
    Lighting light("Lighting", 800, 600);
    light.setMouseCb();
    light.run();

    return 0;
}
