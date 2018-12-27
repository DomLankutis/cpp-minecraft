#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aTexture;
layout (location = 2) in float light;

out vec3 texCoord;
out float Light;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(aPos, 1.0);
    texCoord = aTexture;
    Light = light;
}