#version 440
out vec4 FragColor;
in vec2 TexCoords;

layout(binding = 0) uniform sampler2D tex;
uniform vec3 color;

void main() {
  vec4 tex = texture(tex, TexCoords);
  if (tex.a < 0.2f)
    discard;
  FragColor = tex * vec4(color, 1.0f);
}