#version 450 core
out vec4 o_frag_color;

in vec3 o_box_pos;
in vec3 o_box_normal;
in vec2 o_box_texture;

struct Box {
    sampler2D diffuse_texture;
    sampler2D specular_texture;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform vec3 view_pos;
uniform Box box;
uniform Light light;

void main() {
    // ambient
    vec3 ambient = light.ambient * texture(box.diffuse_texture, o_box_texture).rgb;

    // diffuse 
    vec3 normal = normalize(o_box_normal);
    vec3 light_direction = normalize(light.position - o_box_pos);
    float diff = max(dot(normal, light_direction), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(box.diffuse_texture, o_box_texture).rgb;  

    // specular
    vec3 view_direction = normalize(view_pos - o_box_pos);
    vec3 reflect_direction = reflect(-light_direction, normal);
    float spec = pow(max(dot(view_direction, reflect_direction), 0.0), box.shininess);
    vec3 specular = light.specular * spec * texture(box.specular_texture, o_box_texture).rgb;

    vec3 result = ambient + diffuse + specular;
    o_frag_color = vec4(result, 1.0);
}