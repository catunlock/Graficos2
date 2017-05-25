#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
in vec3 vnormal[];

uniform mat4 modelViewProjectionMatrix;
uniform float time;

void main( void )
{
	const vec3 a = vec3(0,-9.8,0);
	vec3 v = vnormal[0] + vec3(0, 3, 0);
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		vec3 P = gl_in[i].gl_Position.xyz;
		float t = 0.2*time;
		P += v*t + a*t*t;
		gl_Position = modelViewProjectionMatrix * vec4(P,1) ;
		EmitVertex();
	}
    EndPrimitive();
}
