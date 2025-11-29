#pragma once
#include "core/Collider.h"

class RectangleCollider : public Collider {
public:
    RectangleCollider(glm::vec2 position, glm::vec2 size, std::string tag = "")
        : Collider(position, tag), m_size(size) {
        this->m_type = ColliderType::RECTANGLE;
    }

    glm::vec2 getSize() const { return this->m_size; }
    glm::vec2 getMin() const { return this->m_position; }
    glm::vec2 getMax() const { return this->m_position + this->m_size; }

    bool pointInside(glm::vec2 point) const {
        return (point.x >= this->m_position.x) &&
               (point.x <= this->m_position.x + this->m_size.x) &&
               (point.y >= m_position.y) &&
               (point.y <= m_position.y + m_size.y);
    }

    bool intersects(const Collider &other) const override {
        return other.intersectsRectangle(*this);
    }

    bool intersectsCircle(const Collider &other) const override;
    bool intersectsRectangle(const Collider &other) const override;

private:
    glm::vec2 m_size;
};