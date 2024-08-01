#include "blend.h"

int main()
{
    Blend blend = Blend("Blending", 800, 600);

    blend.dropOrBlend(true);
    blend.setMouseCb();
    blend.run();

    return 0;
}