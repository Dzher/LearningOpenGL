#include "woodenbox.h"

int main()
{
    WoodenBox box("Wooden Box", 800, 600);

    box.setMouseCb();
    box.run();

    return 0;
}