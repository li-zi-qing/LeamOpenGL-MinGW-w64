#version 460 core

out vec4 FragColor;
in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

struct Light {
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform Light light;
uniform vec3 viewPos;
//光泽度
uniform float shininess;

void main() {
  vec3 texture_diffuse_color = texture(texture_diffuse1, TexCoords).rgb;
  vec3 texture_specular_color = texture(texture_specular1, TexCoords).rgb;
  
  //环境光
  vec3 ambient = light.ambient * texture_diffuse_color;
  
  //漫反射
  vec3 lightDir = normalize(light.position - FragPos);
  float diff = max(dot(Normal, lightDir), 0.0);
  vec3 diffuse = diff * (texture_diffuse_color * light.diffuse);
  
  //高光
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 refractDir = reflect(-lightDir, Normal);
  float spec = pow(max(dot(viewDir, refractDir), 0.0), shininess);
  vec3 specular = spec * (texture_specular_color * light.specular);
  
  FragColor = vec4(ambient + diffuse + specular, 1.0);
}