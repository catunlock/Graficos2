#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

out vec4 gfrontColor;
out vec3 gnormal;
in vec3 vnormal[];

uniform float d = 0.1f;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 modelViewProjectionMatrix;

uniform mat4 modelMatrixInverse;
uniform mat4 viewMatrixInverse;
uniform mat4 projectionMatrixInverse;
uniform mat4 modelViewMatrixInverse;
uniform mat4 modelViewProjectionMatrixInverse;

uniform mat3 normalMatrix;

const float pi = 3.141592653589793238462643383; 
uniform float time;

vec3 getNormal(vec3 p1, vec3 p2, vec3 p3)
{
	vec3 U = p2 - p1;
	vec3 V = p3 - p1;

	return cross(U,V);
}


void main( void )
{
	gfrontColor = vec4(0.6,0.6,0.6,1);
	
	vec3 N = normalize(vnormal[0] + vnormal[1] + vnormal[2])/3.0f;

	vec3 nv0 = gl_in[0].gl_Position.xyz;
	vec3 nv1 = gl_in[1].gl_Position.xyz;
	vec3 nv2 = gl_in[2].gl_Position.xyz;
	
	vec3 c = (nv0 + nv1 + nv2) / 3.0f;

	float faseX = noise1(9283457);
	float faseY = noise1(2034895);
	vec3 nv3 = c + (d*N);
	
	vec4 v0 = modelViewProjectionMatrix * vec4(nv0,1);
	vec4 v1 = modelViewProjectionMatrix * vec4(nv1,1);
	vec4 v2 = modelViewProjectionMatrix * vec4(nv2,1);

	vec4 v3 = modelViewProjectionMatrix * vec4(nv3,1);
	
	// Bottom
	gnormal = getNormal(nv0,nv1,nv2);
	gl_Position = v0;
	EmitVertex();
	gl_Position = v1;
	EmitVertex();
	gl_Position = v2;
	EmitVertex();
	EndPrimitive();


	// Front
	gnormal = getNormal(nv0,nv1,nv3);
	gl_Position = v0;
	EmitVertex();
	gl_Position = v1;
	EmitVertex();
	gfrontColor	= vec4(1.0,1.0,1.0,1.0);
	gl_Position = v3;
	EmitVertex();
	EndPrimitive();


	// Left
	// LA PUTA ESTA ES LA QUE FALLA.
	gnormal = getNormal(nv2,nv0,nv3);
	gl_Position = v2;
	EmitVertex();
	gl_Position = v0;
	EmitVertex();
	gl_Position = v3;
	EmitVertex();
	EndPrimitive();

	// Right
	gnormal = getNormal(nv1,nv2,nv3);
	gl_Position = v1;
	EmitVertex();
	gl_Position = v2;
	EmitVertex();
	gl_Position = v3;
	EmitVertex();
	EndPrimitive();

}
