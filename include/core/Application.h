#pragma once
#include "core/TImer.h"
#include "game/Game.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
class Application {
public:
    Application(unsigned int height, unsigned int width)
        : m_height(height), m_width(width) {}
    void init();

    void run();

    void shutdown();

private:
    void initGLFW();
    void initGLEW();
    void processInput();
    void update();

    unsigned int m_height;
    unsigned int m_width;
    GLFWwindow *m_window = nullptr;
    double m_accumulatedTime = 0.0;
    const float m_fixedDelta = 1.0f / 60.0f; // 60帧
    Timer m_timer;
    Game m_game;
};