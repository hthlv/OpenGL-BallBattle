#pragma once

#include "core/CircleCollider.h"
#include "core/Texture2D.h"
#include <glm/glm.hpp>
#include <memory>

class Food {
public:
    Food(glm::vec2 position, float radius, glm::vec3 color,
         std::shared_ptr<Texture2D> texture, float value)
        : m_position(position), m_radius(radius), m_color(color),
          m_texture(texture), m_nutritionValue(value) {
        m_collider = std::make_unique<CircleCollider>(
            m_position + glm::vec2(radius), radius, "Food");
    }
    Texture2D *getTexture() { return this->m_texture.get(); }
    glm::vec2 getPosition() const { return this->m_position; }
    glm::vec2 getSize() const { return glm::vec2(this->m_radius); }
    glm::vec3 getColor() const { return this->m_color; }
    float getNutrition() const { return this->m_nutritionValue; }

    Collider *getCollider() const { return m_collider.get(); }

    void destroy() { m_destroyed = true; }
    bool isDestroyed() const { return m_destroyed; }

private:
    glm::vec2 m_position;
    float m_radius;
    float m_nutritionValue; // 营养价值
    glm::vec3 m_color;
    std::shared_ptr<Texture2D> m_texture;
    std::unique_ptr<CircleCollider> m_collider;
    bool m_destroyed = false;
};