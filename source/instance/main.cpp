#include "instance.h"

int main()
{
    glInstance instance = glInstance("Instance", 800, 600);

    instance.useInstance(true);
    instance.setMouseCb();
    instance.run();

    return 0;
}