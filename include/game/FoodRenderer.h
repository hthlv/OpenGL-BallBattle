// 专门用来渲染食物的渲染器
#pragma once
#include "core/Shader.h"
#include "core/Sprite2D.h"
#include <game/Food.h>
#include <memory>
#include <vector>
class FoodRenderer {
public:
    FoodRenderer(std::shared_ptr<Shader> shader);
    void update();
    void draw(glm::mat4 projection);

    // 返回右值引用，允许移动
    const std::vector<Food> &getFoods() const { return this->m_foods; }
    void recordDestroyedIndex(int index);

private:
    std::shared_ptr<Shader> m_shader;
    std::unique_ptr<Sprite2D> m_sprite;
    std::vector<Food> m_foods;

    // 限制食物的数量
    const int FOOD_NUM = 1000;
    // 存储已经销毁的食物索引
    std::vector<int> m_destroyedIndices;
    // 现在还有的食物
    int m_aliveFoodNum = 0;
};