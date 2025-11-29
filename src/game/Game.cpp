#include "game/Game.h"
#include "core/Camera.h"
#include "game/FoodRenderer.h"
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

void Game::init(unsigned int width, unsigned int height) {
    this->m_width = width;
    this->m_height = height;
    loadTextures();
    loadShaders();
    this->m_projection =
        glm::ortho(0.0f, static_cast<float>(this->m_width),
                   static_cast<float>(this->m_height), 0.0f, -1.0f, 100.0f);

    // 相机
    this->m_camera =
        std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 10.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);

    this->m_player = std::make_unique<Player>(rcMgr.getShader("main"));
    this->m_player->setTexture(rcMgr.getTexture("test"));

    // 食物生成器
    m_foodRenderer = std::make_unique<FoodRenderer>(rcMgr.getShader("main"));
    // 线条
    this->m_lineRenderer =
        std::make_unique<Line>(glm::vec2(0.0f, 0.0f), glm::vec2(800.0f, 600.0f),
                               rcMgr.getShader("border"));
}

void Game::update() {
    checkCollision();
    this->m_player->update();
    this->m_foodRenderer->update();

    // 更新相机位置
    this->updateCamera();
    // 更新投影矩阵
    this->updateProjectionMatrix();
}

void Game::draw() {
    drawMapBorder();

    rcMgr.getShader("main")->use();

    if (this->m_camera && this->m_player) {
        rcMgr.getShader("main")->setMat4("view",
                                         this->m_camera->getViewMatrix());
        rcMgr.getShader("main")->setMat4("projection", this->m_projection);
    } else {
        rcMgr.getShader("main")->setMat4("view", glm::mat4(1.0f));
        rcMgr.getShader("main")->setMat4("projection", this->m_projection);
    }

    this->m_foodRenderer->draw(this->m_projection);
    this->m_player->draw();
}

void Game::updateCamera() {
    if (this->m_camera && this->m_player) {
        // 保持相机位置不变
        this->m_camera->setPosition(glm::vec3(0.0f, 0.0f, 10.0f));
        this->m_camera->setYaw(-90.0f);
        this->m_camera->setPitch(0.0f);
    }
}

void Game::updateProjectionMatrix() {
    if (this->m_player) {
        float playerSize = this->m_player->getSize().x;
        glm::vec2 playerPos = this->m_player->getPosition();
        glm::vec2 playerSizeVec = this->m_player->getSize();

        // 计算玩家中心点
        glm::vec2 playerCenter = playerPos + playerSizeVec / 2.0f;

        // 计算缩放因子
        float baseZoom = 1.0f;
        float zoomFactor = baseZoom * (100.0f / std::max(playerSize, 10.0f));
        zoomFactor = std::min(std::max(zoomFactor, 0.5f), 5.0f);

        // 计算视图尺寸
        float viewWidth =
            std::min(static_cast<float>(this->m_width) / zoomFactor,
                     static_cast<float>(this->m_width));
        float viewHeight =
            std::min(static_cast<float>(this->m_height) / zoomFactor,
                     static_cast<float>(this->m_height));

        // 使用玩家中心点计算投影矩阵，但这里有一个重要修复
        // 为了避免抖动，我们需要使用整数坐标或应用平滑处理
        float left = playerCenter.x - viewWidth / 2.0f;
        float right = playerCenter.x + viewWidth / 2.0f;
        float bottom = playerCenter.y + viewHeight / 2.0f;
        float top = playerCenter.y - viewHeight / 2.0f;

        this->m_projection =
            glm::ortho(left, right, bottom, top, -1.0f, 100.0f);
    }
}

void Game::loadTextures() {
    rcMgr.loadTexture("test", "../assets/textures/awesomeface.png");
}

void Game::loadShaders() {
    rcMgr.loadShader("main", "../assets/shaders/sprite.vert",
                     "../assets/shaders/sprite.frag");
    rcMgr.loadShader("border", "../assets/shaders/border.vert",
                     "../assets/shaders/border.frag");
}

void Game::checkCollision() {
    const auto &foods = this->m_foodRenderer->getFoods();
    for (int i = 0; i < foods.size(); ++i) {
        const auto &food = foods[i];
        if (!food.isDestroyed()) {
            if (this->m_player->getCollider()->intersects(
                    *food.getCollider())) {
                this->m_player->eatFood(food);
                const_cast<Food &>(food).destroy();
                this->m_foodRenderer->recordDestroyedIndex(i);
            }
        }
    }
}

// 绘制地图边框
void Game::drawMapBorder() {
    // 使用屏幕坐标系，不随相机移动
    glm::mat4 borderProjection =
        glm::ortho(0.0f, static_cast<float>(this->m_width),
                   static_cast<float>(this->m_height), 0.0f, -1.0f, 1.0f);

    rcMgr.getShader("border")->use();
    rcMgr.getShader("border")->setMat4("view", glm::mat4(1.0f));
    rcMgr.getShader("border")->setMat4("model", glm::mat4(1.0f));
    rcMgr.getShader("border")->setMat4("projection", this->m_projection);

    // 绘制四条边框线（上、右、下、左）
    // 上边线
    this->m_lineRenderer->setPosition(
        glm::vec2(0.0f, 0.0f),
        glm::vec2(static_cast<float>(this->m_width), 0.0f));
    this->m_lineRenderer->draw();

    // 右边线
    this->m_lineRenderer->setPosition(
        glm::vec2(static_cast<float>(this->m_width), 0.0f),
        glm::vec2(static_cast<float>(this->m_width),
                  static_cast<float>(this->m_height)));
    this->m_lineRenderer->draw();

    // 下边线
    this->m_lineRenderer->setPosition(
        glm::vec2(static_cast<float>(this->m_width),
                  static_cast<float>(this->m_height)),
        glm::vec2(0.0f, static_cast<float>(this->m_height)));
    this->m_lineRenderer->draw();

    // 左边线
    this->m_lineRenderer->setPosition(
        glm::vec2(0.0f, static_cast<float>(this->m_height)),
        glm::vec2(0.0f, 0.0f));
    this->m_lineRenderer->draw();
}