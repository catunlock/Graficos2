#version 330 core

uniform float radius = 1.0;
uniform mat4 modelViewProjectionMatrix;

layout (location = 0) in vec3 vertex;

out vec2 vtexCoord;

void main() {
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.);
    vtexCoord = (4.0/radius)*(vertex.xy+vertex.zx);
}