#version 330 core

in vec4 gfrontColor;
out vec4 fragColor;
in vec3 gnormal;
in vec2 gtexCoords;

uniform mat3 normalMatrix;

uniform sampler2D colorMap;

vec3 colors[6] = vec3[](vec3(1.0f,0.0f,0.0f), 
                        vec3(0.0f,1.0f,0.0f),
                        vec3(0.0f,0.0f,1.0f),
                        vec3(1.0f,1.0f,0.0f),
                        vec3(0.0f,1.0f,1.0f),
                        vec3(1.0f,0.0f,1.0f));

int selectColor() {

    int selected = 0;
    float min = distance(gfrontColor.xyz, colors[selected]);
    for (int i = 0; i < 6; ++i) {
        float d = distance(gfrontColor.xyz, colors[i]);
        if (d < min) {
            min = d;
            selected = i;
        }
    }

    return selected;
}

void main()
{
  
    vec3 N = normalize(normalMatrix * gnormal);
    int s = selectColor();
    fragColor = vec4(colors[s],1) * N.z;
    if (normalize(gnormal).y > 0.5f) {
        fragColor *= texture(colorMap, gtexCoords);
    }


    
  
}
