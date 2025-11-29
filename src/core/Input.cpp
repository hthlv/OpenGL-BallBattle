#include "core/Input.h"
#include "GLFW/glfw3.h"
// 静态成员初始化
std::unordered_map<unsigned int, bool> Input::m_pressed;
glm::vec2 Input::m_mousePosition = {0, 0};
GLFWwindow *Input::m_window = nullptr;

void Input::init(GLFWwindow *window) {
    m_window = window;

    // 设置回调函数
    glfwSetKeyCallback(m_window, Input::keyCallback);
    glfwSetCursorPosCallback(m_window, Input::mouseCallback);

    // 初始鼠标位置
    double x, y;
    glfwGetCursorPos(m_window, &x, &y);
    m_mousePosition = {x, y};
}

void Input::keyCallback(GLFWwindow *, int key, int, int action, int) {
    switch (action) {
    case GLFW_PRESS:
    case GLFW_REPEAT:
        m_pressed[key] = true;
        break;
    case GLFW_RELEASE:
        m_pressed[key] = false;
        break;
    }
}

void Input::mouseCallback(GLFWwindow *, double xpos, double ypos) {
    m_mousePosition = {xpos, ypos};
}

bool Input::isPressed(unsigned int key) {
    auto it = m_pressed.find(key);
    return (it != m_pressed.end()) ? it->second : false;
}

glm::vec2 Input::getMousePosition() {
    // 转换为float返回（兼容glm::vec2）
    return {static_cast<float>(m_mousePosition.x),
            static_cast<float>(m_mousePosition.y)};
}