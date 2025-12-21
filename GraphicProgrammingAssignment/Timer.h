#pragma once

#include <Windows.h>
#include <chrono>

class Timer
{
public:
    Timer();

    void Reset();
    void Tick();
    float GetDeltaTime() const;
    float GetTotalTime() const;

private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point previousTime;

    float deltaTime;
    float totalTime;
};