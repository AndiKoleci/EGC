#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position[3];
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

// TODO(student): Declare any other uniforms
uniform int isInSpotlight;
uniform vec3 object_color;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    float total_light = 0;
    float ambient_light = 0.25 * material_kd;

    for(int i = 0; i < 3; i++){
        vec3 N = normalize(world_normal);
        vec3 L = normalize( light_position[i] - world_position );
        vec3 V = normalize( eye_position - world_position );
        vec3 H = normalize( L + V );
        vec3 R = reflect (-L, N);

        float diffuse_light = material_kd * max(dot(N, L), 0);
        float specular_light = 0;
        float attenuate = 1/pow(distance(light_position[i], world_position), 2);
        // It's important to distinguish between "reflection model" and
        // "shading method". In this shader, we are experimenting with the Phong
        // (1975) and Blinn-Phong (1977) reflection models, and we are using the
        // Phong (1975) shading method. Don't mix them up!
        if (diffuse_light > 0)
        {
            specular_light = material_ks * 1 * pow(max(dot(V, R), 0), material_shininess); 
        }

        // TODO(student): If (and only if) the light is a spotlight, we need to do
        // some additional things.
        float light = 0;
        if(isInSpotlight == 1) {
            float cut_off = radians(30.0);
            float spot_light = dot(-L, light_direction);
            float spot_light_limit = cos(cut_off);

            float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            float light_att_factor = pow(linear_att, 2);

            if(spot_light > cos(cut_off)){
            
                light = 0 + light_att_factor * attenuate * (diffuse_light + specular_light);
            }
            else{
                light = 0;

            }
        }
        else{
            light = attenuate * (diffuse_light + specular_light);

        }
        total_light+=light;
    }
    // TODO(student): Define ambient, diffuse and specular light components
   

    vec3 color = (total_light + ambient_light) * object_color;
    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.

    // TODO(student): Write pixel out color
    out_color = vec4(color, 1);

}
