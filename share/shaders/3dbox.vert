#version 450 core
layout(location = 0) in vec3 box_pos;
layout(location = 1) in vec2 texture_coord;

out vec2 out_texture_coord;

uniform mat4 model_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;

void main() {
    gl_Position = projection_mat * view_mat * model_mat * vec4(box_pos, 1.0);
    out_texture_coord = vec2(texture_coord.x, 1.0 - texture_coord.y);
}