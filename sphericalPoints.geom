#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

out vec4 gfrontColor;
out vec3 gnormal;
out vec2 gtexCoords;

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


uniform float step = 0.3f;
const float s = 1.0f;

vec3 calcNormal(vec3 p1, vec3 p2, vec3 p3)
{
	vec3 U = p2 - p1;
	vec3 V = p3 - p1;

	return cross(U,V);
}


void main( void )
{
	gfrontColor = vec4(0.5f,0.5f,0.5f,1);
	
	vec3 c = (modelViewMatrix * ((gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position) / 3.0f)).xyz;
	
	float s = step/2.0f;

	vec3 nv1 = c+ vec3(-s, s,  s);
	vec3 nv2 = c+ vec3(-s, -s, s);
	vec3 nv3 = c+ vec3(s, -s,  s);
	vec3 nv4 = c+ vec3(s, s,   s);

	vec2 st1 = vec2(0,0);
	vec2 st2 = vec2(0,1);
	vec2 st3 = vec2(1,1);
	vec2 st4 = vec2(1,0);

	vec4 v1 = projectionMatrix * vec4(nv1, 1);
	vec4 v2 = projectionMatrix * vec4(nv2, 1);
	vec4 v3 = projectionMatrix * vec4(nv3, 1);
	vec4 v4 = projectionMatrix * vec4(nv4, 1);
	 
	// CARA 1 = FRONT
	// DOWN
	gnormal = calcNormal(nv1,nv2,nv3);
	gtexCoords = vec2(1,1);
	gl_Position = v1;
	EmitVertex();
	gtexCoords = vec2(0,1);
	gl_Position = v2;
	EmitVertex();
	gtexCoords = vec2(0,0);
	gl_Position = v3;
	EmitVertex();
	EndPrimitive();

	// UP
	gl_Position = v1;
	gtexCoords = vec2(1,1);
	EmitVertex();
	gl_Position = v3;
	gtexCoords = vec2(0,0);
	EmitVertex();
	gl_Position = v4;
	gtexCoords = vec2(0,1);
	EmitVertex();
	EndPrimitive();

	

}

