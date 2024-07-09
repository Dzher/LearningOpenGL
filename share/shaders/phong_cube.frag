#version 450 core
out vec4 fragment_color;

in vec3 fragment_position;
in vec3 the_cube_normal_vector;

uniform vec3 light_position;
uniform vec3 light_color;
uniform vec3 object_color;

void main() {
    float ambient_strength = 0.1;
    vec3 ambient_light = ambient_strength * light_color;

    vec3 normal = normalize(the_cube_normal_vector);
    vec3 light_direction = normalize(light_position - fragment_position);

    vec3 diffuse_light = max(dot(normal, light_direction), 0.0) * light_color;

    vec3 result_light = (ambient_light + diffuse_light) * object_color;

    fragment_color = vec4(result_light, 1.0);
}