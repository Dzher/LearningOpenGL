#include "faceculling.h"

int main()
{
    FaceCull blend = FaceCull("Face Culling", 800, 600);

    blend.cull(true);
    blend.setCullFace(CullFace::Front);
    blend.setMouseCb();
    blend.run();

    return 0;
}