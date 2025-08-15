#version 460 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D Texture;
uniform vec4 lightColor;

void main() {
  FragColor = (lightColor * 0.5) + (texture(Texture, TexCoords).rgba * 0.5);
}