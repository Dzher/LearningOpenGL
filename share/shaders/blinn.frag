#version 450 core
out vec4 frag_color;

in VS_OUT
{
    vec3 pos;
    vec3 normal;
    vec2 texture;
}
fs_in;

uniform sampler2D plane_texture;
uniform vec3 light_pos;
uniform vec3 view_pos;
uniform bool blinn;

void main()
{
    vec3 color = texture(plane_texture, fs_in.texture).rgb;
    vec3 light_direction = normalize(light_pos - fs_in.pos);
    vec3 normal_direction = normalize(fs_in.normal);
    vec3 view_direction = normalize(view_pos - fs_in.pos);
    vec3 reflect_direction = reflect(-light_direction, normal_direction);

    float ambient_factor = 0.05;
    vec3 ambient_light = ambient_factor * color;

    float diffuse_factor = max(dot(light_direction, normal_direction), 0.0);
    vec3 diffuse_light = diffuse_factor * color;

    float specular_factor = 0.0;
    if(blinn)
    {
        vec3 half_way_direction = normalize(light_direction + view_direction);
        specular_factor = pow(max(dot(normal_direction, half_way_direction), 0.0), 32.0);
    }
    else
    {
        specular_factor = pow(max(dot(view_direction, reflect_direction), 0.0), 8.0);
    }
    vec3 specular_light = specular_factor * color;

    frag_color = vec4(ambient_light + diffuse_light + specular_light, 1.);
}