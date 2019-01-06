#version 410 core
out vec4 outColor;

in vec3 texCoord;
in float Light;

uniform sampler2DArray tex;

void main()
{
    if (gl_FragCoord.x >= 955 && gl_FragCoord.x <= 965 && gl_FragCoord.y >= 535 && gl_FragCoord.y <= 545) {
        outColor = vec4(1, 1, 1, 1);
    } else {
        outColor = vec4(texture(tex, texCoord).rgb * ((Light / 30) + 0.05), 1);
    }
}