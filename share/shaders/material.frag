#version 450 core
out vec4 fragment_color;

struct CubeMaterial {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient_strength;
    vec3 diffuse_strength;
    vec3 specular_strength;
};

in vec3 cube_fragment_position;
in vec3 out_cube_fragment_normal;

uniform vec3 view_position;
uniform CubeMaterial cube_material;
uniform Light light_strength;

void main() {
    vec3 ambient_light = cube_material.ambient * light_strength.ambient_strength;

    vec3 normal = normalize(out_cube_fragment_normal);
    vec3 light_direction = normalize(light_strength.position - cube_fragment_position);
    vec3 diffuse_light = max(dot(light_direction, normal), 0.0) * cube_material.diffuse * light_strength.diffuse_strength;

    vec3 view_direction = normalize(view_position - cube_fragment_position);
    vec3 reflect_direction = reflect(-view_direction, normal);
    vec3 specular_light = pow(max(dot(reflect_direction, view_direction), 0.0), cube_material.shininess) * cube_material.specular * light_strength.specular_strength;

    fragment_color = vec4(ambient_light + diffuse_light + specular_light, 1.0);
}