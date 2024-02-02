#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
out vec3 fragColor;

uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(inPosition, 1.0);
    fragColor = inColor;
}