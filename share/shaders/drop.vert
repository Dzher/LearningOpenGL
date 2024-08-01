#version 450 core
layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec2 in_texture_coord;

out vec2 texture_coord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    gl_Position = projection * view * model * vec4(in_pos, 1.);
    texture_coord = in_texture_coord;
}