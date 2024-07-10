#version 450 core
out vec4 fragment_color;

in vec3 fragment_position;
in vec3 the_cube_normal_vector;

uniform bool is_ambient_light = false;
uniform bool is_diffuse_light = false;
uniform bool is_specular_light = false;

uniform vec3 light_position;
uniform vec3 view_position;

uniform vec3 light_color;
uniform vec3 object_color;

void main() {
    float ambient_strength = 0.1;
    vec3 ambient_light = ambient_strength * light_color;
    vec3 ambient_light_result = ambient_light * object_color;
    if(is_ambient_light) {
        fragment_color = vec4(ambient_light_result, 1.0);
        return;
    }

    vec3 normal = normalize(the_cube_normal_vector);
    vec3 light_direction = normalize(light_position - fragment_position);

    vec3 diffuse_light = max(dot(normal, light_direction), 0.0) * light_color;
    vec3 diffuse_light_result = (ambient_light + diffuse_light) * object_color;
    if(is_diffuse_light) {
        fragment_color = vec4(diffuse_light_result, 1.0);
        return;
    }

    float specular_strength = 0.5;
    vec3 view_direction = normalize(view_position - fragment_position);
    vec3 reflect_direction = reflect(-view_direction, normal);
    vec3 specular_light = specular_strength * pow(max(dot(view_direction, reflect_direction), 0.0), 32) * light_color;

    vec3 specular_light_result = (ambient_light + diffuse_light + specular_light) * object_color;
    if(is_specular_light) {
        fragment_color = vec4(specular_light_result, 1.0);
    }
}