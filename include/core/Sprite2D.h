#pragma once

#include "core/Shader.h"
#include "core/Texture2D.h"
#include <memory>

class Sprite2D {
public:
    Sprite2D(std::shared_ptr<Shader> shader);
    ~Sprite2D() {}

    void draw(Texture2D &texture, glm::vec2 position = glm::vec2(0.0f),
              glm::vec2 size = glm::vec2(100.0f, 100.0f), float rotate = 0.0f,
              glm::vec3 color = glm::vec3(1.0f));

private:
    std::shared_ptr<Shader> m_shader;
    Texture2D m_texture;
    unsigned int m_VAO;
    void initData();
    glm::mat4 m_model;
};