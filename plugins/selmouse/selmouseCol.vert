#version 330 core

layout (location = 0) in vec3 vertex;

uniform mat4 viewProjectionMatrix;

void main()
{
	gl_Position    = viewProjectionMatrix*vec4(vertex,1.0);
	
}