#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

const float areamax = 0.5f;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelMatrix;

void main( void )
{
	// 1
	vec3 v0 = (modelViewMatrix * gl_in[0].gl_Position).xyz;
	vec3 v1 = (modelViewMatrix * gl_in[1].gl_Position).xyz;
	vec3 v2 = (modelViewMatrix * gl_in[2].gl_Position).xyz;

	vec3 u = v1 - v0;
	vec3 v = v2 - v0;
	
	// 2
	float area = length(cross(u,v));
	area *= 500;
	

	// 3
	gfrontColor = vec4(mix(vec3(1,0,0),vec3(1,1,0), area),1.0f);
	//gfrontColor = vec4(1,0,1,1);
	for( int i = 0 ; i < 3 ; i++ )
	{
		
		gl_Position = modelViewProjectionMatrix * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
}
