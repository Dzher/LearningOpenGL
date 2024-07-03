#version 450 core
out vec4 fragment_color;
in vec2 out_texture_coord;

uniform sampler2D texture_0;

void main() {
    fragment_color = texture(texture_0, out_texture_coord);
}