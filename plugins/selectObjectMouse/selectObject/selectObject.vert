#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

uniform vec3 center;
uniform vec3 scale;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(N.z, N.z, N.z,1.0);
    //frontColor = vec4(1.0, 1.0, 1.0, 1.0);

    vec3 newVertex = vertex * scale;
    newVertex = newVertex + center;

    gl_Position = modelViewProjectionMatrix * vec4(newVertex, 1.0);
}