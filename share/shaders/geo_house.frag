#version 450 core
out vec4 frag_color;

in vec3 fs_color;

void main()
{
    frag_color = vec4(fs_color, 1.);
}