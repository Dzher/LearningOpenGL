#version 450 core
layout(location = 0) in vec3 vertex_pos;
layout(location = 2) in vec2 texture_coord;

out vec2 out_texture_coord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    gl_Position = projection * view * model * vec4(vertex_pos, 1.f);
    out_texture_coord = texture_coord;
}