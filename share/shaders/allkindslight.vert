#version 450 core
layout(location = 0) in vec3 in_box_position;
layout(location = 1) in vec3 in_fragment_normal;
layout(location = 2) in vec2 in_texture_coord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 out_fragment_position;
out vec3 out_fragment_normal;
out vec2 out_texture_coord;

void main() {
    out_fragment_position = vec3(model * vec4(in_box_position, 1.0));

    out_fragment_normal = mat3(transpose(inverse(model))) * in_fragment_normal;

    out_texture_coord = in_texture_coord;

    gl_Position = projection * view * model * vec4(in_box_position, 1.0);
}