#pragma once
#include "core/Collider.h"
#include "core/Sprite2D.h"
#include "core/Texture2D.h"
#include "game/Food.h"
#include "game/GameObject.h"
#include <glm/glm.hpp>
#include <memory>
class Player : public GameObject {
public:
    Player() {}
    Player(std::shared_ptr<Shader> shader);

    void init() override;
    void update() override;
    void draw() override;
    void onCollision(Collider *other) override;
    void setTexture(std::shared_ptr<Texture2D> texture) {
        this->m_texture = texture;
    }
    void eatFood(const Food &food);
    glm::vec2 getPosition() const { return this->m_position; }
    glm::vec2 getSize() const { return this->m_size; }

private:
    float m_moveSpeed = 1.0f;
    glm::vec2 m_position = glm::vec2(0.0f);
    glm::vec2 m_size = glm::vec2(10.0f);
    float m_rotation = 0.0f;
    glm::vec3 m_color = glm::vec3(1.0f);
    std::shared_ptr<Texture2D> m_texture;
    std::unique_ptr<Sprite2D> m_sprite;
};