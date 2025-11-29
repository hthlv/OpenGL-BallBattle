#include "core/TImer.h"
#include <GLFW/glfw3.h>
#include <memory>

Timer::Timer() : m_impl(std::make_unique<Impl>()) { reset(); }

void Timer::reset() {
    double now = this->now();
    m_impl->startTime = now;
    m_impl->lastFrameTime = now;
    m_impl->totalTime = 0.0;
}

double Timer::elapsed() const { return this->now() - m_impl->startTime; }

double Timer::elapsedMillis() const { return elapsed() * 1000.0; }

// 应该每帧调用
double Timer::frameDelta() const {
    double currentTime = this->now();
    m_deltaTime = currentTime - m_impl->lastFrameTime;
    m_impl->lastFrameTime = currentTime;
    m_impl->totalTime += m_deltaTime;
    return m_deltaTime;
}

double Timer::totalTime() const { return m_impl->totalTime; }

double Timer::now() const { return glfwGetTime(); }