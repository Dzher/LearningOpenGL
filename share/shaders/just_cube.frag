#version 450 core
in vec3 the_light_color;
out vec4 cube_fragment_color;

uniform vec3 cube_color;

void main() {
    cube_fragment_color = vec4(cube_color * the_light_color, 1.0);
}