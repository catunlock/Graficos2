#version 330 core

in vec3 vs_normalEyeSpace;
in vec4 vs_vertexEyeSpace; 
out vec4 fragColor;

uniform vec4 lightAmbient;  // similar a gl_LightSource[0].ambient
uniform vec4 lightDiffuse;  // similar a gl_LightSource[0].diffuse
uniform vec4 lightSpecular; // similar a gl_LightSource[0].specular
uniform vec4 lightPosition; // similar a gl_LightSource[0].position; en eye space
uniform vec4 matAmbient;    // similar a gl_FrontMaterial.ambient 
uniform vec4 matDiffuse;    // similar a gl_FrontMaterial.diffuse 
uniform vec4 matSpecular;   // similar a gl_FrontMaterial.specular
uniform float matShininess; // similar a gl_FrontMaterial.shininess

void main()
{

    vec4 ambient = matAmbient * lightAmbient;
        
    vec3 N = normalize(vs_normalEyeSpace);
    vec3 L = normalize((lightPosition - vs_vertexEyeSpace).xyz);
    float dotNL = max(0.0, dot(N,L));
    vec4 diffuse = matDiffuse * lightDiffuse * dotNL;
        
    vec3 H = normalize(vec3(0.0, 0.0, 1.0) + L);
    float dotNH = pow(max(0.0, dot(N,H)), matShininess);
    vec4 specular = matSpecular * lightSpecular * dotNH;
    
    fragColor = ambient + diffuse + specular;
}
