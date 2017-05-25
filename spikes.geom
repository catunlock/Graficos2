#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

out vec4 gfrontColor;
out vec3 gnormal;
in vec3 vnormal[];
in vec3 vcolor[];

uniform float d = 3.0f;
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

uniform vec4 lightAmbient;  // similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse;  // similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular; // similar a gl_LightSource[0].specular
uniform vec4 lightPosition; // similar a gl_LightSource[0].position; en eye space
uniform vec4 matAmbient;    // similar a gl_FrontMaterial.ambient 
uniform vec4 matDiffuse;    // similar a gl_FrontMaterial.diffuse 
uniform vec4 matSpecular;   // similar a gl_FrontMaterial.specular
uniform float matShininess; // similar a gl_FrontMaterial.shininess

uniform vec3 boundingBoxMin; // cantonada minima de la capsa englobant 
uniform vec3 boundingBoxMax; // cantonada maxima de la capsa englobant

uniform vec2 mousePosition;  // coordenades del cursor (window space; origen a la cantonada inferior esquerra)

vec3 getNormal(vec3 p1, vec3 p2, vec3 p3)
{
	vec3 U = p2 - p1;
	vec3 V = p3 - p1;

	return cross(U,V);
}


void main( void )
{	
	vec3 N = normalize(vnormal[0] + vnormal[1] + vnormal[2])/3.0f;

	vec3 nv0 = gl_in[0].gl_Position.xyz;
	vec3 nv1 = gl_in[1].gl_Position.xyz;
	vec3 nv2 = gl_in[2].gl_Position.xyz;
	
	vec3 nv3 = ((nv0 + nv1 + nv2) / 3.0f) + getNormal(nv0,nv1,nv2)*d;

	vec4 v0 = modelViewProjectionMatrix * vec4(nv0,1);
	vec4 v1 = modelViewProjectionMatrix * vec4(nv1,1);
	vec4 v2 = modelViewProjectionMatrix * vec4(nv2,1);
	vec4 v3 = modelViewProjectionMatrix * vec4(nv3,1);
	

	// Base
	gnormal = getNormal(nv0,nv1,nv2);
	gfrontColor = vec4(vcolor[0],1.0f);
	gl_Position = v0;
	EmitVertex();
	gfrontColor = vec4(vcolor[1],1.0f);
	gl_Position = v1;
	EmitVertex();
	gfrontColor = vec4(vcolor[2],1.0f);
	gl_Position = v2;
	EmitVertex();
	EndPrimitive();



	// Front
	gnormal = getNormal(nv0,nv1,nv3);
	gfrontColor = vec4(vcolor[0],1.0f);
	gl_Position = v0;
	EmitVertex();
	gfrontColor = vec4(vcolor[1],1.0f);
	gl_Position = v1;
	EmitVertex();
	gfrontColor = vec4(1.0f);
	gl_Position = v3;
	EmitVertex();
	EndPrimitive();


	// Left
	gnormal = getNormal(nv2,nv0,nv3);
	gfrontColor = vec4(vcolor[2],1.0f);
	gl_Position = v2;
	EmitVertex();
	gfrontColor = vec4(vcolor[0],1.0f);
	gl_Position = v0;
	EmitVertex();
	gfrontColor = vec4(1.0f);
	gl_Position = v3;
	EmitVertex();
	EndPrimitive();

	// Right
	gnormal = getNormal(nv1,nv2,nv3);
	gl_Position = v1;
	gfrontColor = vec4(vcolor[1],1.0f);
	EmitVertex();
	gl_Position = v2;
	gfrontColor = vec4(vcolor[2],1.0f);
	EmitVertex();
	gl_Position = v3;
	gfrontColor = vec4(1.0f);
	EmitVertex();
	EndPrimitive();
}
