#include "multilights.h"

int main()
{
    MultiLights box("Multiple Light", 800, 600);

    box.setMouseCb();
    box.run();

    return 0;
}