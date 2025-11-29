#pragma once

#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include <unordered_map>
class Input {
public:
    // 绑定回调函数
    static void init(GLFWwindow *window);
    // 按键是否被按下
    static bool isPressed(unsigned int key);
    // 获取鼠标位置
    static glm::vec2 getMousePosition();

private:
    // 键盘处理
    static void keyCallback(GLFWwindow *window, int key, int scancode,
                            int action, int mods);
    // 鼠标位置处理
    static void mouseCallback(GLFWwindow *window, double xpos, double ypos);

private:
    static std::unordered_map<unsigned int, bool> m_pressed;
    static glm::vec2 m_mousePosition;
    static GLFWwindow *m_window;
};