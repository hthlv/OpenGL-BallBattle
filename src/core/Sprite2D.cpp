#include "core/Sprite2D.h"
#include "core/Shader.h"
#include "core/Texture2D.h"
#include "glm/ext/matrix_transform.hpp"
#include <glm/gtc/matrix_transform.hpp>

Sprite2D::Sprite2D(std::shared_ptr<Shader> shader) : m_shader(shader) {
    this->initData();
}

void Sprite2D::initData() {
    unsigned int VBO;
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f};

    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(this->m_VAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite2D::draw(Texture2D &texture, glm::vec2 position, glm::vec2 size,
                    float rotate, glm::vec3 color) {
    this->m_shader->use();
    this->m_model = glm::mat4(1.0f);
    this->m_model = glm::translate(this->m_model, glm::vec3(position, 0.0f));
    this->m_model = glm::translate(
        this->m_model,
        glm::vec3(0.5f * size.x, 0.5f * size.y,
                  0.0f)); // move origin of rotation to center of quad
    this->m_model = glm::rotate(this->m_model, glm::radians(rotate),
                                glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    this->m_model =
        glm::translate(this->m_model, glm::vec3(-0.5f * size.x, -0.5f * size.y,
                                                0.0f)); // move origin back
    this->m_model = glm::scale(this->m_model, glm::vec3(size, 1.0f));

    this->m_shader->setMat4("model", this->m_model);
    this->m_shader->setVec3("color", color);
    texture.bind();

    glBindVertexArray(this->m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}