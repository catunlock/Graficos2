#version 330 core
uniform mat4 modelViewProjectionMatrix;

in vec3 vertex;
in vec3 color;
void main() {
	gl_Position = modelViewProjectionMatrix * vec4(vertex,1.0);
}