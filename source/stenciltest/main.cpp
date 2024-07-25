#include "stenciltest.h"

int main()
{
    StencilTest box("All Kinds Light", 800, 600);

    box.setMouseCb();

    box.run();

    return 0;
}