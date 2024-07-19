#version 330 core
out vec4 frag_color;

struct Box {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cut_off;
    float outer_cutoff;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

#define NR_POINT_LIGHTS 4

in vec3 o_box_fragment_position;
in vec3 o_box_fragment_normal;
in vec2 o_box_texture_coord;

uniform vec3 view_position;
uniform Light direction_light;
uniform PointLight point_lights[NR_POINT_LIGHTS];
uniform SpotLight spot_light;
uniform Box box;

// function prototypes
vec3 calcDirectionLight(Light light, vec3 normal, vec3 viewDir);
vec3 calcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {    
    // properties
    vec3 box_fragment_normal = normalize(o_box_fragment_normal);
    vec3 view_direction = normalize(view_position - o_box_fragment_position);

    // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    // phase 1: directional lighting
    vec3 result = calcDirectionLight(direction_light, box_fragment_normal, view_direction);
    // phase 2: point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++) {
        result += calcPointLight(point_lights[i], box_fragment_normal, o_box_fragment_position, view_direction);
    }    
    // phase 3: spot light
    result += calcSpotLight(spot_light, box_fragment_normal, o_box_fragment_position, view_direction);

    frag_color = vec4(result, 1.0);
}

vec3 calcDirectionLight(Light light, vec3 normal, vec3 view_direction) {
    vec3 light_direction = normalize(-light.direction);
    // diffuse shading
    float diffue_factor = max(dot(normal, light_direction), 0.0);
    // specular shading
    vec3 reflect_direction = reflect(-light_direction, normal);
    float specular_factor = pow(max(dot(view_direction, reflect_direction), 0.0), box.shininess);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(box.diffuse, o_box_texture_coord));
    vec3 diffuse = light.diffuse * diffue_factor * vec3(texture(box.diffuse, o_box_texture_coord));
    vec3 specular = light.specular * specular_factor * vec3(texture(box.specular, o_box_texture_coord));
    return (ambient + diffuse + specular);
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 frag_pos, vec3 view_direction) {
    vec3 light_direction = normalize(light.position - frag_pos);
    // diffuse shading
    float diffue_factor = max(dot(normal, light_direction), 0.0);
    // specular shading
    vec3 reflect_direction = reflect(-light_direction, normal);
    float specular_factor = pow(max(dot(view_direction, reflect_direction), 0.0), box.shininess);
    // attenuation
    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(box.diffuse, o_box_texture_coord));
    vec3 diffuse = light.diffuse * diffue_factor * vec3(texture(box.diffuse, o_box_texture_coord));
    vec3 specular = light.specular * specular_factor * vec3(texture(box.specular, o_box_texture_coord));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 frag_pos, vec3 view_direction) {
    vec3 light_direction = normalize(light.position - frag_pos);
    // diffuse shading
    float diffue_factor = max(dot(normal, light_direction), 0.0);
    // specular shading
    vec3 reflect_direction = reflect(-light_direction, normal);
    float specular_factor = pow(max(dot(view_direction, reflect_direction), 0.0), box.shininess);
    // attenuation
    float distance = length(light.position - frag_pos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(light_direction, normalize(-light.direction));
    float epsilon = light.cut_off - light.outer_cutoff;
    float intensity = clamp((theta - light.outer_cutoff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(box.diffuse, o_box_texture_coord));
    vec3 diffuse = light.diffuse * diffue_factor * vec3(texture(box.diffuse, o_box_texture_coord));
    vec3 specular = light.specular * specular_factor * vec3(texture(box.specular, o_box_texture_coord));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}