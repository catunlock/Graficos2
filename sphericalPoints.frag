#version 330 core

in vec4 gfrontColor;
out vec4 fragColor;
in vec3 gnormal;
in vec2 gtexCoords;
uniform mat3 normalMatrix;

uniform sampler2D colorMap;

void main()
{
    vec4 c = texture(colorMap, gtexCoords);
    if (c.a != 1.0) {
        discard;
    }
    fragColor = c;
}
