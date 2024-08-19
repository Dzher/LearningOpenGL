#include "geoshader.h"

int main()
{
    GeoShader shader = GeoShader("Geometry Shader", 800, 600);

    // shader.setDrawType(GeoShader::GeoType::House);
    // shader.setDrawType(GeoShader::GeoType::Boom);
    shader.setDrawType(GeoShader::GeoType::Normal);
    shader.setMouseCb();
    shader.run();

    return 0;
}