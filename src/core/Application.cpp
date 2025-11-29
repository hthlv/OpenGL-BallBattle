#include "core/Application.h"

#include "GLFW/glfw3.h"
#include "core/Input.h"
#include "core/Shader.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
using std::cout;
using std::endl;

void Application::init() {
    initGLFW();
    initGLEW();

    // 垂直同步
    glfwSwapInterval(1);

    Input::init(m_window);

    this->m_game.init(this->m_width, this->m_height);
}

void Application::update() {
    // 更新
    this->m_game.update();
}

void Application::run() {
    while (!glfwWindowShouldClose(this->m_window)) {
        this->processInput();
        this->m_accumulatedTime += this->m_timer.frameDelta();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        while (this->m_accumulatedTime >= m_fixedDelta) {
            this->update();
            this->m_accumulatedTime -= this->m_timer.m_deltaTime;
        }

        m_game.draw();

        glfwSwapBuffers(this->m_window);
        glfwPollEvents();
    }
}

void Application::shutdown() {
    // 在这里清理资源
    glfwDestroyWindow(this->m_window);
    glfwTerminate();
}

void Application::processInput() {
    if (Input::isPressed(GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(this->m_window, true);
    }
}

void Application::initGLFW() {
    // 初始化glfw
    if (glfwInit() == GLFW_FALSE) {
        cout << "Init GLFW Failed" << endl;
        return;
    }
    // 设置OpenGL版本
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    // 设置核心模式配置文件
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // 设置窗口大小固定
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // 创建窗口 - 修复参数顺序
    m_window = glfwCreateWindow(this->m_width, this->m_height, "Ball Battle",
                                nullptr, nullptr);
    if (this->m_window == nullptr) {
        cout << "Create GLFW Window Failed!" << endl;
        glfwTerminate();
        return;
    }

    // 设置OpenGL上下文
    glfwMakeContextCurrent(m_window);
}

void Application::initGLEW() {
    // 初始化glew
    if (glewInit() != GLEW_OK) {
        cout << "Init GLEW failed" << endl;
        glfwTerminate();
        return;
    }
}