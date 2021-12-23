#include "stdafx.h"
#include "Timer.h"

Timer::Timer(class Tool* const tool) :
	ISubsystem(tool)
{
}

bool Timer::Initialize()
{
	prev_time = std::chrono::high_resolution_clock::now();
	return true;
}

void Timer::Update()
{
	auto current_time = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> ms = current_time - prev_time;
	prev_time = current_time;
	delta_time_ms = ms.count();
}

Stopwatch::Stopwatch()
{
	Start();
}

void Stopwatch::Start()
{
	start_time = std::chrono::high_resolution_clock::now();
}

auto Stopwatch::GetElapsedTimeMs() const -> const float
{
	std::chrono::duration<double, std::milli> ms = std::chrono::high_resolution_clock::now() - start_time;
	return static_cast<float>(ms.count());
}

auto Stopwatch::GetElapsedTimeSec() const -> const float
{
	return GetElapsedTimeMs() / 1000.f;
}
