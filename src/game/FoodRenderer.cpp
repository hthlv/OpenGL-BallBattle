#include "game/FoodRenderer.h"
#include "core/ResourceManager.h"
#include "core/Shader.h"
#include "core/Sprite2D.h"
#include "game/Food.h"
#include "glm/fwd.hpp"
#include <algorithm>
#include <iostream>
#include <memory>
#include <random>

FoodRenderer::FoodRenderer(std::shared_ptr<Shader> shader) : m_shader(shader) {
    this->m_sprite = std::make_unique<Sprite2D>(this->m_shader);
}

void FoodRenderer::update() {
    // 先移除被摧毁的食物
    m_foods.erase(
        std::remove_if(m_foods.begin(), m_foods.end(),
                       [](const Food &food) { return food.isDestroyed(); }),
        m_foods.end());

    // 使用随机数控制生成数量
    std::random_device rd;
    std::mt19937 gen(rd());
    int maxGenerate = FOOD_NUM - static_cast<int>(m_foods.size());

    if (maxGenerate > 0) {
        std::uniform_int_distribution<int> numDist(0, maxGenerate);
        int needGenerate = numDist(gen);

        if (needGenerate > 0) {
            std::uniform_real_distribution<float> xposDist(0, 800.0f);
            std::uniform_real_distribution<float> yposDist(0, 600.0f);
            std::uniform_real_distribution<float> sizeDist(1.0f, 10.0f);
            std::uniform_real_distribution<float> colorDist(0.2f, 1.0f);
            std::uniform_real_distribution<float> nutritionDist(0.1, 1.0f);

            for (int i = 0; i < needGenerate; ++i) {
                glm::vec2 position(xposDist(gen), yposDist(gen));
                float radius = sizeDist(gen);
                glm::vec3 color(colorDist(gen), colorDist(gen), colorDist(gen));
                float nutrition = nutritionDist(gen);
                auto texture = ResourceManager::instance().getTexture("test");
                this->m_foods.emplace_back(position, radius, color, texture,
                                           nutrition);
            }

            std::cout << "Generated " << needGenerate
                      << " new foods. Total: " << m_foods.size() << std::endl;
        }
    }
}

void FoodRenderer::draw(glm::mat4 projection) {
    this->m_shader->use();
    this->m_shader->setMat4("projection", projection);
    // 绘制食物
    for (auto &food : m_foods) {
        if (!food.isDestroyed()) {
            this->m_sprite->draw(*food.getTexture(), food.getPosition(),
                                 food.getSize(), 0.0f, food.getColor());
        }
    }
}

void FoodRenderer::recordDestroyedIndex(int index) {
    m_destroyedIndices.push_back(index);
    --this->m_aliveFoodNum;
}