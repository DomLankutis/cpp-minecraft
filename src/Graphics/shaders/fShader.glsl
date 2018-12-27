#version 410 core
out vec4 outColor;

in vec3 texCoord;
in float Light;

uniform sampler2DArray tex;

void main()
{
    outColor = vec4(texture(tex, texCoord).rgb * (Light / 15 + 0.1), 1);
}