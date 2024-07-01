#version 450 core

in vec3 out_color;
in vec2 out_text_coord;

uniform sampler2D the_texture;

void main()
{
    FragColor = texture(the_texture, out_text_coord);
}