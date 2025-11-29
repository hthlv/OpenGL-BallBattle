#pragma once

#include "core/Shader.h"
#include <glm/glm.hpp>
#include <memory>

class Line {
public:
    Line() = default;
    Line(glm::vec2 start, glm::vec2 end, std::shared_ptr<Shader> shader);
    ~Line();

    void draw();
    void setPosition(glm::vec2 start, glm::vec2 end);

private:
    glm::vec2 m_start, m_end;
    void initData();

    std::shared_ptr<Shader> m_shader;
    unsigned int m_VAO, m_VBO;
};