#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec3 aTexture;

out vec3 texCoord;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(aPos, 1.0);
    texCoord = aTexture;
}