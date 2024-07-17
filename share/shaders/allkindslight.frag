#version 450 core
out vec4 frag_color;

in vec3 out_fragment_position;
in vec3 out_fragment_normal;
in vec2 out_texture_coord;

struct Box {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 direction;
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Box box;
uniform Light light;
uniform vec3 view_position;

uniform bool is_parallel = false;
uniform bool is_point = false;
uniform bool is_spot = false;
uniform bool is_torch = false;

void main() {
    vec3 ambient = light.ambient * texture(box.diffuse, out_texture_coord).rgb;

    vec3 normal = normalize(out_fragment_normal);

    vec3 light_direction;
    if(is_parallel) {
        light_direction = normalize(-light.direction);
    } else {
        light_direction = normalize(light.position - out_fragment_normal);
    }

    float diffuse_factor = max(dot(-light.direction, normal), 0.0);
    vec3 diffuse = diffuse_factor * light.diffuse * texture(box.diffuse, out_texture_coord).rgb;

    vec3 view_direction = normalize(view_position - out_fragment_position);
    vec3 reflect_direction = reflect(-light_direction, normal);
    float specular_factor = pow(max(dot(view_direction, reflect_direction), 0.0), box.shininess);
    vec3 specular = specular_factor * light.specular * texture(box.specular, out_texture_coord).rgb;

    vec3 result = ambient + diffuse + specular;
    frag_color = vec4(result, 1.0);
}
