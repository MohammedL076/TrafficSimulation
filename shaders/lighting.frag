#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D texture_diffuse1;

struct DirLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;
uniform vec3 viewPos;

void main()
{
    vec3 ambient = dirLight.ambient * texture(texture_diffuse1, TexCoord).rgb;
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-dirLight.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = dirLight.diffuse * diff * texture(texture_diffuse1, TexCoord).rgb;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = dirLight.specular * spec;
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
