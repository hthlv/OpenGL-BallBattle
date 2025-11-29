#include "core/CircleCollider.h"
#include "core/Collider.h"
#include "core/RectangleCollider.h"

// 圆形VS圆形
bool CircleCollider::intersectsCircle(const Collider &other) const {
    const CircleCollider &circle = static_cast<const CircleCollider &>(other);
    float distance = glm::length(this->m_position - circle.getPosition());
    return distance < (this->m_radius + circle.getRadius());
}
// 圆形VS矩形
bool CircleCollider::intersectsRectangle(const Collider &other) const {
    const RectangleCollider &rect =
        static_cast<const RectangleCollider &>(other);
    // 最近点在矩形边界上的位置
    float closestX = glm::clamp(m_position.x, rect.getMin().x, rect.getMax().x);
    float closestY = glm::clamp(m_position.y, rect.getMin().y, rect.getMax().y);

    // 计算圆心到最近点的距离
    glm::vec2 centerToPoint = glm::vec2(closestX, closestY) - m_position;
    return length(centerToPoint) < m_radius;
}
// 矩形VS圆形
bool RectangleCollider::intersectsCircle(const Collider &other) const {
    return other.intersectsRectangle(*this);
}
// 矩形VS矩形
bool RectangleCollider::intersectsRectangle(const Collider &other) const {
    const RectangleCollider &rect =
        static_cast<const RectangleCollider &>(other);
    return this->getMin().x <= rect.getMax().x &&
           this->getMax().x >= rect.getMin().x &&
           this->getMin().y <= rect.getMax().y &&
           this->getMax().y >= rect.getMin().y;
}