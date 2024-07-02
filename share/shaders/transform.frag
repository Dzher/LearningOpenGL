#version 450 core

in vec2 out_texture_coord;

out vec4 fragment_color;

uniform sampler2D texture_0;
uniform sampler2D texture_1;

void main() {
    fragment_color = mix(texture(texture_0, out_texture_coord), texture(texture_1, out_texture_coord), 0.5);
}