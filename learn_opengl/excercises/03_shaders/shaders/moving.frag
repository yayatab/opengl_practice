#version 330 core

out vec4 FragColor;

in vec3 pos;

uniform float opacity;

void main() {
    FragColor = vec4(pos, opacity);
}