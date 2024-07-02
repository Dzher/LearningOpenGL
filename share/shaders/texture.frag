#version 450 core

out vec4 fragment_color;

in vec3 out_color;
in vec2 out_text_coord;

uniform bool normal;
uniform bool colorful;
uniform bool mixed;

uniform sampler2D the_texture_0;
uniform sampler2D the_texture_1;

void main() {
    if(normal) {
        fragment_color = texture(the_texture_0, out_text_coord);
    }
    if(colorful) {
        fragment_color = texture(the_texture_0, out_text_coord) * vec4(out_color, 1.0);
    }
    if(mixed) {
        fragment_color = mix(texture(the_texture_0, out_text_coord), texture(the_texture_1, out_text_coord), 0.5);
    }
}