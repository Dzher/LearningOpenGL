#version 450 core

out vec4 fragment_color;

in vec3 out_color;
in vec2 out_text_coord;

uniform sampler2D the_texture;

void main() {
    // fragment_color = texture(the_texture, out_text_coord);
    fragment_color = texture(the_texture, out_text_coord) * vec4(out_color, 1.0);
}