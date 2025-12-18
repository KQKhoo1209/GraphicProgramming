#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <Windows.h>

class Timer
{
public:
    Timer();

    void Update();
    float GetDeltaTime() const;

private:
    DWORD lastTime;
    float deltaTime;
};

#endif