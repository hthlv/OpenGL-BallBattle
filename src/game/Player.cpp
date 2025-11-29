#include "game/Player.h"
#include "core/CircleCollider.h"
#include "core/Collider.h"
#include "core/Input.h"
#include "core/Sprite2D.h"
#include "game/GameObject.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <random>

Player::Player(std::shared_ptr<Shader> shader) : GameObject(shader) {
    this->init();
}

void Player::init() {
    // 玩家初始位置随机
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> xposDist(0, 795.0f);
    std::uniform_real_distribution<float> yposDist(0, 595.0f);
    this->m_position = glm::vec2(xposDist(gen), yposDist(gen));

    this->m_collider =
        std::make_unique<CircleCollider>(this->m_position + this->m_size / 2.0f,
                                         this->m_size.x / 2.0f, "Player");
    this->m_sprite = std::make_unique<Sprite2D>(this->m_shader);
}

void Player::update() {
    if (Input::isPressed(GLFW_KEY_W)) {
        this->m_position.y -= m_moveSpeed;
    }
    if (Input::isPressed(GLFW_KEY_S)) {
        this->m_position.y += m_moveSpeed;
    }
    if (Input::isPressed(GLFW_KEY_A)) {
        this->m_position.x -= m_moveSpeed;
    }
    if (Input::isPressed(GLFW_KEY_D)) {
        this->m_position.x += m_moveSpeed;
    }
    // 防止玩家出界
    if (this->m_position.x < 0.0f) {
        this->m_position.x = 0.0f;
    }
    if (this->m_position.x > 800 - this->m_size.x) {
        this->m_position.x = 800 - this->m_size.x;
    }
    if (this->m_position.y < 0.0f) {
        this->m_position.y = 0.0f;
    }
    if (this->m_position.y > 600 - this->m_size.y) {
        this->m_position.y = 600 - this->m_size.y;
    }
    if (this->m_collider) {
        this->m_collider->setPosition(this->m_position + this->m_size / 2.0f);
    }
}

void Player::draw() {
    this->m_shader->use();
    this->m_sprite->draw(*this->m_texture, this->m_position, this->m_size,
                         this->m_rotation, this->m_color);
}

void Player::onCollision(Collider *other) {
    if (this->m_collider->intersects(*other)) {
        std::cout << "Player collided with: " << other->getTag() << std::endl;
        if (other->getTag() == "Food") {
            // glm::vec2 rebound = m_position - other->getPosition();
            // m_position += glm::normalize(rebound) * 5.0f;
        }
    }
}

void Player::eatFood(const Food &food) {
    // 可配置的增长参数
    const float MIN_GROWTH = 0.1f;  // 最小增长量
    const float MAX_GROWTH = 5.0f;  // 最大增长量
    const float DECAY_RATE = 0.05f; // 衰减率

    // 计算基础增长量
    float baseGrowth = food.getNutrition();

    // 应用衰减：growth = baseGrowth / (1 + decayRate * currentSize)
    float growth = baseGrowth / (1.0f + DECAY_RATE * (this->m_size.x));

    // 限制增长范围
    growth = std::max(MIN_GROWTH, std::min(growth, MAX_GROWTH));

    this->m_size += glm::vec2(growth);

    std::cout << "Player size: " << this->m_size.x << ", Growth: " << growth
              << std::endl;

    if (auto circleCollider =
            dynamic_cast<CircleCollider *>(this->m_collider.get())) {
        circleCollider->setRadius(this->m_size.x / 2.0f);
    }
}