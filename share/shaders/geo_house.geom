#version 450 core
layout(points) in;
layout(triangle_strip, max_vertices = 5) out;

in VS_OUT
{
    vec3 color;
}
gs_in[];

out vec3 fs_color;

void build_house(vec4 position)
{
    fs_color = gs_in[0].color;
    gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0); // 1:bottom-left   
    EmitVertex();
    gl_Position = position + vec4(0.2, -0.2, 0.0, 0.0); // 2:bottom-right
    EmitVertex();
    gl_Position = position + vec4(-0.2, 0.2, 0.0, 0.0); // 3:top-left
    EmitVertex();
    gl_Position = position + vec4(0.2, 0.2, 0.0, 0.0); // 4:top-right
    EmitVertex();
    gl_Position = position + vec4(0.0, 0.4, 0.0, 0.0); // 5:top
    fs_color = vec3(1.0, 1.0, 1.0); // don't change the position
    EmitVertex();
    EndPrimitive();
}

void main()
{
    build_house(gl_in[0].gl_Position);
}