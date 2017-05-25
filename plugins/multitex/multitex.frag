 #version 330 core
 uniform sampler2D sampler0;
 uniform sampler2D sampler1;
 in vec2 vtexCoord;
 out vec4 fragColor;
 void main() {
    fragColor =  mix(texture(sampler0, vtexCoord),
    texture(sampler1, vtexCoord), 0.5); 
}