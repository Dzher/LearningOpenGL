#version 450 core
in vec3 the_light_color;
out vec4 light_fragment_color;

void main() {
    light_fragment_color = vec4(the_light_color, 1.0);
}