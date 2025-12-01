#version 440
out vec4 FragColor;
in vec2 TexCoords;
in vec3 FragPos;

layout(binding = 0) uniform sampler2D tex;
uniform vec3 color;

// 点光源属性
struct PointLight {
  vec3 position;
  vec3 color;
  float intensity;
};
uniform PointLight pointLight;

uniform bool usePointLight;

void main() {
  vec4 texColor = texture(tex, TexCoords);
  if (texColor.a < 0.2f)
    discard;
  if (usePointLight) {
    // 计算到光源的距离
    float distance = length(FragPos.xy - pointLight.position.xy);

    // 计算衰减
    float attenuation =
        1.0 / (1.0 + 0.1 * distance + 0.01 * (distance * distance));

    // 应用光照
    vec3 ambient = 0.5 * pointLight.color;
    vec3 diffuse = pointLight.color * attenuation * pointLight.intensity;

    // 最终颜色 = 纹理颜色 * (环境光 + 漫反射光)
    vec3 result = (ambient + diffuse) * texColor.rgb * color;

    FragColor = vec4(result, texColor.a);
  } else {
    FragColor = texColor * vec4(color, 1.0);
  }
}