#version 330 core
uniform vec4 setColor;

in vec2 myTexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D ourTexture;
uniform vec4 lightColor;
uniform vec3 lightPos;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor.rgb;

    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor.rgb;
    vec4 texColor = texture(ourTexture, myTexCoord);
    vec3 result = (ambient+diffuse) * texColor.rgb;
   
   FragColor = vec4(result,1.0);
}