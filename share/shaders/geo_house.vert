#version 450 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec3 color;

out VS_OUT {
    vec3 color;
} vs_out;

void main() {
    vs_out.color = color;
    gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);
}