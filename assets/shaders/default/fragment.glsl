#version 120

uniform sampler2D diffuseMap;
uniform float brightness;

void main(void) {
  gl_FragColor = texture2D(diffuseMap, gl_TexCoord[0].st) * brightness;
}