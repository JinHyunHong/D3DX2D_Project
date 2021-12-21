#pragma once

class Timer final :
	public ISubsystem
{
public:
	Timer(class Tool* const tool);
	~Timer() = default;

	bool Initialize() override;
	void Update() override;
	void Destroy() override {};

	auto GetDeltaTimeMs() const -> float { return static_cast<float>(delta_time_ms); }
	auto GetDeltaTimeSec() const -> float { return static_cast<float>(delta_time_ms / 1000.0); }
	
private:
	double delta_time_ms = 0.0;
	std::chrono::time_point<std::chrono::high_resolution_clock> prev_time;
};

class Stopwatch final
{
public:
	Stopwatch();
	~Stopwatch() = default;

	void Start();

	auto GetElapsedTimeMs() const -> const float;
	auto GetElapsedTimeSec() const -> const float;

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

};