#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;
in vec3 vnormal[];

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

uniform float time;
uniform float speed = 0.1f;
uniform float angSpeed = 1.0f;
uniform float d = 0.5f;

void main( void )
{
	vec3 n = (vnormal[0] + vnormal[1] + vnormal[2])/3.0f;
	vec3 centroTriangulo = (gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position).xyz / 3.0f;

	float a = angSpeed * time;
	mat3 roty = mat3(cos(a), sin(a), 0,
				-sin(a), cos(a), 0,
					0,0,1);

	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		vec3 newVector = (roty * (centroTriangulo - gl_in[i].gl_Position.xyz)) + centroTriangulo;

		gl_Position = modelViewProjectionMatrix * (vec4(newVector + (time*n*d),1));
		EmitVertex();
	}
    EndPrimitive();
}
