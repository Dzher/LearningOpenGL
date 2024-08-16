#include "geoshader.h"

int main()
{
    GeoShader shader = GeoShader("Geometry Shader", 800, 600);

    shader.setDrawType(GeoShader::GeoType::House);
    shader.setMouseCb();
    shader.run();

    return 0;
}