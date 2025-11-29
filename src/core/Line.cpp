#include "core/Line.h"
#include "core/Shader.h"
#include "glm/fwd.hpp"
#include <glm/gtc/matrix_transform.hpp>

Line::Line(glm::vec2 start, glm::vec2 end, std::shared_ptr<Shader> shader)
    : m_start(start), m_end(end), m_shader(shader) {
    this->initData();
}

Line::~Line() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}

void Line::initData() {
    unsigned int VBO;
    // 初始化为足够大的空间，能容纳矩形的5个顶点
    float vertices[] = {m_start.x, m_start.y, m_end.x, m_end.y};

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(this->m_VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    this->m_VBO = VBO;
}

void Line::draw() {
    this->m_shader->use();

    // 绘制线条
    glBindVertexArray(this->m_VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
}

void Line::setPosition(glm::vec2 start, glm::vec2 end) {
    this->m_start = start;
    this->m_end = end;
    // 更新顶点数据
    float vertices[] = {start.x, start.y, end.x, end.y};

    glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}