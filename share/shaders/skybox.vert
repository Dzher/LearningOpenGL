#version 450 core
layout(location = 0) in vec3 pos;

out vec3 texture_coord;

uniform mat4 projection;
uniform mat4 view;

void main() {
    texture_coord = pos;
    vec4 modified_pos = projection * view * vec4(pos, 1.);
    gl_Position = modified_pos.xyww;
}