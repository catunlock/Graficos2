#version 330 core
out vec4 fragColor;

void main() {
      if (mod((gl_FragCoord.y-0.5), float(5)) > 0.0) discard;
      fragColor=vec4(1.0f,0,0,1.0f);
}
