#version 330 core
out vec4 frag_color;

in vec2 texture_coord;

uniform sampler2D texture1;

void main() {
    vec4 texture_color = texture(texture1, texture_coord);
    if(texture_color.a <= 0.1) {
        discard;
    }
    frag_color = texture_color;
}