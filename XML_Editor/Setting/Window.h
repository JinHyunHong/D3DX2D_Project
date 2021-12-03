#pragma once

enum class WindowSplitType : uint
{
	Unknown,
	Main,
	Left,
	Right
};

class window final
{
public:
	window(const WindowSplitType& type, const HINSTANCE& instance, 
		const uint& width, const uint& height);
	~window();

public:
	const bool Initalize();
	const bool Update();

public:
	auto GetType() const -> const WindowSplitType& { return type; }

	auto GetClientWidth() const -> const uint& { return width; }
	void SetClientWidth(const uint& width) { this->width = width; }

	auto GetClientHegiht() const -> const uint& { return height; }
	void SetClientHegiht(const uint& height) { this->height = height; }

	auto GetWindowHandle() const -> const HWND& { return handle; }
	void SetWindowHandle(const HWND& handle) { this->handle = handle; }

	auto GetInstance() const -> const HINSTANCE& { return instance; }
	void SetInstance(const HINSTANCE& instance) { this->instance = instance; }

	auto GetParent() const -> const std::shared_ptr<window>& { return parent; }
	void SetParent(const std::shared_ptr<window>& parent) {this->parent = parent;}

	auto GetChilds() const -> const std::vector<std::shared_ptr<window>>& { return childs; }
	auto GetChild(const WindowSplitType& type)->std::shared_ptr<window>;

	void AddChild(const std::shared_ptr<window>& child);

	void DrawTextWindow(const std::string& text);


public:
	const bool Create();
	void Show();
	void Destroy();

private:
	WindowSplitType type = WindowSplitType::Unknown;
	uint width = 0;
	uint height = 0;
	HWND handle = nullptr;
	HINSTANCE instance = nullptr;
	std::shared_ptr<window> parent;
	std::vector<std::shared_ptr<window>> childs;

public:
	static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK SubLeftWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK SubRightWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
};