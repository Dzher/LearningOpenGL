#version 450 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texture;

out VS_OUT
{
    vec3 pos;
    vec3 normal;
    vec2 texture;
}
vs_out;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    vs_out.pos = pos;
    vs_out.normal = normal;
    vs_out.texture = texture;

    gl_Position = projection * view * vec4(pos, 1.);
}