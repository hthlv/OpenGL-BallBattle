#pragma once
#include "core/Collider.h"
#include "core/Shader.h"
#include <memory>

class GameObject {
public:
    GameObject() = default;
    GameObject(std::shared_ptr<Shader> shader) : m_shader(shader) {}
    virtual ~GameObject() {}

    virtual void init() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    // 碰撞处理
    virtual void onCollision(Collider *other) = 0;

    void setCollider(std::unique_ptr<Collider> collider) {
        this->m_collider = std::move(collider);
    }
    void setShader(std::shared_ptr<Shader> shader) { this->m_shader = shader; }

    Collider *getCollider() const { return this->m_collider.get(); }

protected:
    std::shared_ptr<Shader> m_shader;
    std::unique_ptr<Collider> m_collider;
};