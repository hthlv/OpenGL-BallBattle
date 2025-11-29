#pragma once
#include "core/Collider.h"

class CircleCollider : public Collider {
public:
    CircleCollider(glm::vec2 center, float radius, std::string tag = "")
        : Collider(center, tag), m_radius(radius) {
        this->m_type = ColliderType::CIRCLE;
    }

    float getRadius() const { return this->m_radius; }
    void setRadius(float radius) { this->m_radius = radius; }

    bool intersects(const Collider &other) const override {
        return other.intersectsCircle(*this);
    }

    bool intersectsCircle(const Collider &other) const override;
    bool intersectsRectangle(const Collider &other) const override;

private:
    float m_radius;
};