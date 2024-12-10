#version 330 core
layout (location = 0) out vec4 fragColor;
uniform sampler2D texture;
uniform vec2 res;
uniform mat3 view;
uniform mat4 projection;

void main() {
    vec2 uv = vec2(0);
    vec2 texpos = vec2(0);
    fragColor = texture2D(texture, texpos);
}