#pragma once

class Core
{
public:
	static Core& GetInst()
	{
		static Core inst;
		return inst;
	}

	bool Initialize(HINSTANCE instance, const uint& width, const uint& height);
	bool Update();
	void Render();
	void Destroy();

	auto GetInstance() const -> const HINSTANCE& { return instance; }
	auto GetTool()	const -> class Tool* { return tool; }

	auto GetWindow() -> std::shared_ptr<class window>& { return current_window; }

	auto GetWidth() const -> const uint& { return width; }
	auto GetHeight() const -> const uint& { return height; }

private:
	Core() = default;
	~Core();

private:
	class Tool* tool = nullptr;
	std::shared_ptr<class window> current_window;
	HINSTANCE instance = nullptr;
	uint width = 0;
	uint height = 0;
};