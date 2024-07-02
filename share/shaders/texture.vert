#version 450 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 text_coord;

out vec3 out_color;
out vec2 out_text_coord;

void main() {
    gl_Position = vec4(pos, 1.0);
    out_color = color;
    out_text_coord = vec2(text_coord.x, text_coord.y);
}