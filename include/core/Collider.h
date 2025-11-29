#pragma once
#include <glm/glm.hpp>
#include <string>

enum ColliderType { CIRCLE, RECTANGLE, POINT };

class Collider {
public:
    Collider(glm::vec2 position, std::string tag = "")
        : m_position(position), m_tag(tag) {}

    virtual ~Collider() = default;

    // 碰撞检测接口
    virtual bool intersects(const Collider &other) const = 0;
    virtual bool intersectsCircle(const Collider &other) const = 0;
    virtual bool intersectsRectangle(const Collider &other) const = 0;

    ColliderType getType() const { return this->m_type; }
    glm::vec2 getPosition() const { return this->m_position; }
    void setPosition(glm::vec2 position) { this->m_position = position; }

    // 标签用于过滤碰撞检测 (e.g., "Player", "Enemy", "Item")
    const std::string &getTag() const { return this->m_tag; }

protected:
    glm::vec2 m_position;
    std::string m_tag;
    ColliderType m_type;
};