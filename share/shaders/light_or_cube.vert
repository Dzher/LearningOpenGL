#version 450 core
layout(location = 0) in vec3 light_pos;
out vec3 the_light_color;

uniform vec3 light_color;

uniform mat4 model_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;

void main() {
    gl_Position = projection_mat * view_mat * model_mat * vec4(light_pos, 1.0);
    the_light_color = light_color;
}