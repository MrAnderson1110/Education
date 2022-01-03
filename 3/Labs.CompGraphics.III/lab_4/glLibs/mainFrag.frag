#version 330

out vec4 color;

in vec3 Normal;
in vec3 FragPos;

struct light {
    vec3 color;
    vec3 position;
};

uniform light[3] lights;
uniform vec3 objectColor;
uniform vec3 viewPos;
uniform float specStrength;
uniform float specIntensity;
uniform int lightCount;


vec3 calcColor(light defLight) {
    //Ambient
        float ambientStrength = 0.3f;
        vec3 ambient = ambientStrength * defLight.color;
    //Deffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(defLight.position - FragPos);
        float diffAngle = max(dot(norm, lightDir), 0.0f);
        vec3 diffuse = diffAngle * defLight.color;
    //Specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float specAngle = pow(max(dot(viewDir, reflectDir), 0.0), specStrength);
        vec3 specular = specIntensity * specAngle * defLight.color;
    //Result
        return (ambient + diffuse + specular);
}

void main(void)
{
    vec3 result;
    for(int i = 0; i < 3; ++i) {
        result += calcColor(lights[i]);
    }
    result *= objectColor;
    color = vec4(result, 1.0f);
}
