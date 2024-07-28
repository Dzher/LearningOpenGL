#version 450 core
out vec4 frag_color;

in vec2 box_texture_coord;

uniform sampler2D the_texture;

void main() {
    frag_color = texture(the_texture, box_texture_coord);
}