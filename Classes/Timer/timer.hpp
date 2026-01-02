#pragma once

#include <chrono>

class Timer {
private:
    std::chrono::time_point<std::chrono::steady_clock> start_;
    std::chrono::time_point<std::chrono::steady_clock> end_;
    bool running_;

public:
    Timer();

    void start();
    void time();
};