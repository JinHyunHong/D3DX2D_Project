#pragma once

enum class Dialog_type
{
	Unknown,
	AddElement,
	AddAttribute
};


class window final
{
public:
	window(class Tool* const tool, const HINSTANCE& instance, const uint& width, const uint& height);
	~window();

public:
	const bool Initialize();
	const bool Update();

public:
	auto GetClientWidth() const -> const uint& { return width; }
	void SetClientWidth(const uint& width) { this->width = width; }

	auto GetClientHeight() const -> const uint& { return height; }
	void SetClientHeight(const uint& height) { this->height = height; }

	auto GetWindowHandle() const -> const HWND& { return handle; }
	void SetWindowHandle(const HWND& handle) { this->handle = handle; }

	auto GetInstance() const -> const HINSTANCE& { return instance; }
	void SetInstance(const HINSTANCE& instance) { this->instance = instance; }

	void DrawTextWindow(const std::string& text);
	void EraseTextsWindow();


public:
	const bool Create(const wchar_t* class_name, const wchar_t* window_name);
	void Show();
	void Destroy();

private:
	class Tool* tool = nullptr;
	HINSTANCE instance = nullptr;
	uint width = 0;
	uint height = 0;
	HWND handle = nullptr;

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
};