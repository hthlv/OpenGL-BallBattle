#pragma once
#include "core/Camera.h"
#include "core/Line.h"
#include "core/ResourceManager.h"
#include "game/FoodRenderer.h"
#include "game/GameObject.h"
#include "game/Player.h"
#include <memory>
class Game {
public:
    Game() = default;
    void init(unsigned int width, unsigned int height);
    void update();
    void draw();
    void setWindowHeight(unsigned int height) { this->m_height = height; }
    void setWindowWidth(unsigned int width) { this->m_width = width; }

private:
    void loadShaders();
    void loadTextures();
    void checkCollision();
    void updateCamera();
    void updateProjectionMatrix();

    glm::mat4 m_projection;
    unsigned int m_width;
    unsigned int m_height;
    std::unique_ptr<Player> m_player;

    std::vector<GameObject *> m_gameObjects;
    ResourceManager &rcMgr = ResourceManager::instance();

    // 食物生成器
    std::unique_ptr<FoodRenderer> m_foodRenderer;

    // 相机
    std::unique_ptr<Camera> m_camera;

    // 线条
    std::unique_ptr<Line> m_lineRenderer;
    // 绘制边框
    void drawMapBorder();
};