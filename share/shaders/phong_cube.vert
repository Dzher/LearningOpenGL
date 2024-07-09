#version 450 core
layout(location = 0) in vec3 cube_position;
layout(location = 1) in vec3 cube_normal_vector;

out vec3 fragment_position;
out vec3 the_cube_normal_vector;

uniform mat4 model_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;

void main() {
    fragment_position = vec3(model_mat * vec4(cube_position, 1.0));
    the_cube_normal_vector = cube_normal_vector;

    gl_Position = projection_mat * view_mat * model_mat * vec4(cube_position, 1.0);
}