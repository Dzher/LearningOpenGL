#version 450 core
layout(location = 0) in vec3 i_box_pos;
layout(location = 1) in vec3 i_box_normal;
layout(location = 2) in vec2 i_box_texture;

out vec3 o_box_pos;
out vec3 o_box_normal;
out vec2 o_box_texture;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    gl_Position = projection * view * model * vec4(i_box_pos, 1.0);
    o_box_pos = vec3(model * vec4(i_box_pos, 1.0));
    o_box_normal = normalize(i_box_normal);
    o_box_texture = i_box_texture;
}
