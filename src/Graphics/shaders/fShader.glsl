#version 410 core
out vec4 outColor;

in vec3 texCoord;

uniform sampler2DArray tex;

void main()
{
    outColor = texture(tex, vec3(texCoord.xy, texCoord.z));
}