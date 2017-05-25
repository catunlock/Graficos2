 #version 330 core
 uniform sampler2D sampler0;
 uniform sampler2D sampler1;
 uniform sampler2D sampler2;
 in vec2 vtexCoord;
 out vec4 fragColor;
 void main() {

    float r = texture(sampler2, vtexCoord).r; 
    fragColor =  mix(texture(sampler0, vtexCoord), texture(sampler1, vtexCoord), r); 
}