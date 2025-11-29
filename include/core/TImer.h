#pragma once

#include <memory>

class Timer {
public:
    Timer();
    // 重新开始计时
    void reset();
    // 返回以秒为单位的时间
    double elapsed() const;
    // 返回以毫秒为单位的时间
    double elapsedMillis() const;
    // 获取增量时间
    double frameDelta() const;
    // 获取全部事件
    double totalTime() const;

public:
    mutable double m_deltaTime = 0.0;

private:
    struct Impl {
        double startTime = 0.0;
        double lastFrameTime = 0.0;
        double totalTime = 0.0;
        double deltaTime = 0.0;
    };
    double now() const;
    std::unique_ptr<Impl> m_impl;
};