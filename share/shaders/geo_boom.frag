#version 450 core
in vec2 texture_coord;
out vec4 frag_color;

uniform sampler2D texture_diffuse1;

void main()
{
    frag_color = texture(texture_diffuse1, texture_coord);
}