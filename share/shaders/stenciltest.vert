#version 450 core
layout(location = 0) in vec3 box_position;
layout(location = 1) in vec2 box_texture;

out vec2 box_texture_coord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    gl_Position = projection * view * model * vec4(box_position, 1.0);
    box_texture_coord = box_texture;
}