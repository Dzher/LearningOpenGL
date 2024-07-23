#include "firstmodel.h"

int main()
{
    FirstMode model("First Model", 800, 600);

    model.setMouseCb();

    model.run();

    return 0;
}