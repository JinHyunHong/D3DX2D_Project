#pragma once

class Core
{
public:
	static Core& GetInst()
	{
		static Core inst;
		return inst;
	}

private:
	Core() = default;
	~Core();

public:
	bool Initialize(HINSTANCE instance, const uint& width, const uint& height);
	bool Update();
	void Destroy();

	auto AddWindow(const WindowSplitType& type) -> const std::shared_ptr<window>;
	auto GetWindow(const WindowSplitType& type) const -> const std::shared_ptr<window>;

private:
	class Tool* tool = nullptr;
	std::vector<std::shared_ptr<window>> windows;
	HINSTANCE instance = nullptr;
	uint width = 0;
	uint height = 0;
};