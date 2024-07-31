#version 450 core
out vec4 frag_color;

in vec2 out_texture_coord;

uniform sampler2D texture_diffuse1;

void main() {
    frag_color = texture(texture_diffuse1, out_texture_coord);
}