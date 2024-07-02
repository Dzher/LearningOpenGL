#version 450 core

layout(location = 0) in vec3 postion;
layout(location = 1) in vec2 texture_coord;

out vec2 out_texture_coord;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(postion, 1.0);
    out_texture_coord = vec2(texture_coord);
}