#version 330 core

in vec3 Color;

out vec4 FragColor;

void main() {
    // Assignez la couleur transmise depuis le vertex shader avec un alpha de 1
    FragColor = vec4(Color, 1.0);
}
