#include "allkindslight.h"

int main()
{
    AllKindsLight box("Wooden Box", 800, 600);

    box.setMouseCb();
    box.run();

    return 0;
}