#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aNormal;
layout (location = 2) in vec2 aColor;
layout (location = 3) in vec2 aTexture;

out vec2 TexCoord;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(aPos, 1.0);
    TexCoord = aTexture;
}