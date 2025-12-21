#include "Timer.h"

Timer::Timer()
	: deltaTime(0.0f), totalTime(0.0f)
{
	Reset();
}

void Timer::Reset()
{
	startTime = std::chrono::high_resolution_clock::now();
	previousTime = startTime;
	totalTime = 0.0f;
	deltaTime = 0.0f;
}

void Timer::Tick()
{
	auto currentTime = std::chrono::high_resolution_clock::now();

	// Calculate delta time: (Current Time - Previous Time)
	std::chrono::duration<float> delta = currentTime - previousTime;
	deltaTime = delta.count();

	// Calculate total time: (Current Time - Start Time)
	std::chrono::duration<float> total = currentTime - startTime;
	totalTime = total.count();

	// Update previousTime to be the current time for the next frame
	previousTime = currentTime;
}

float Timer::GetDeltaTime() const
{
	return deltaTime;
}

float Timer::GetTotalTime() const
{
	return totalTime;
}