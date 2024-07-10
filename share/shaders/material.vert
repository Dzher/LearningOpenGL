#version 450 core
layout(location = 0) in vec3 cube_position;
layout(location = 1) in vec3 in_cube_fragment_normal;

out vec3 cube_fragment_position;
out vec3 out_cube_fragment_normal;

uniform mat4 model_mat;
uniform mat4 view_mat;
uniform mat4 projection_mat;

void main() {
    cube_fragment_position = vec3(model_mat * vec4(cube_position, 1.0));
    out_cube_fragment_normal = normalize(in_cube_fragment_normal);

    gl_Position = projection_mat * view_mat * model_mat * vec4(cube_position, 1.0);
}