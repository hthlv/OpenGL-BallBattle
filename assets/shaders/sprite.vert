#version 440
layout(location = 0) in vec4 vertex;

out vec2 TexCoords;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
  TexCoords = vertex.zw;
  FragPos = (model * vec4(vertex.xy, 0.0, 1.0)).xyz;
  gl_Position = projection * view * vec4(FragPos, 1.0);
}