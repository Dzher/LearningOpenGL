#version 450 core
layout(location = 0) in vec3 box_position;
layout(location = 1) in vec3 box_fragment_normal;
layout(location = 2) in vec2 box_texture_coord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 o_box_fragment_position;
out vec3 o_box_fragment_normal;
out vec2 o_box_texture_coord;

void main() {
    o_box_fragment_position = vec3(model * vec4(box_position, 1.0));
    o_box_fragment_normal = mat3(transpose(inverse(model))) * box_fragment_normal;
    o_box_texture_coord = box_texture_coord;
    gl_Position = projection * view * model * vec4(box_position, 1.0);
}