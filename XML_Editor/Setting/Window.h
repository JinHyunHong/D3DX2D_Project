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

	auto GetDialog(const Dialog_type& type);
	auto GetDialog(const HWND& handle) const -> const std::shared_ptr<class Dialog>;
	auto GetDialogEmptyHandle() const->const Dialog_type;

	void CreateInDialog(const Dialog_type& type, const int& resource_id);
	void AddDialogHandle(const Dialog_type& type, const HWND& handle);

	auto GetDialogType(const std::shared_ptr<class Dialog>& dialog) const -> const Dialog_type;


public:
	const bool Create();
	void Show();
	void Destroy();

private:
	class Tool* tool = nullptr;
	HINSTANCE instance = nullptr;
	uint width = 0;
	uint height = 0;
	HWND handle = nullptr;
	std::unordered_map<Dialog_type, std::shared_ptr<class Dialog>> dialogs;

public:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
};