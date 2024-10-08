#include "allkindslight.h"

int main()
{
    AllKindsLight box("All Kinds Light", 800, 600);

    box.setMouseCb();

    box.setLight(KindsOfLight::ParallelLight);
    // box.setLight(KindsOfLight::PointLight);
    // box.setLight(KindsOfLight::SpotLight);
    // box.setLight(KindsOfLight::Torch);

    box.run();

    return 0;
}