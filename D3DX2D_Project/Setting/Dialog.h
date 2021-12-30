#pragma once

class Dialog
{
public:
	Dialog(class Tool* const tool);
	~Dialog() = default;

	bool Initialize(HINSTANCE instance, HWND parent_handle, const int& Resource_id);

	auto GetHandle() const -> const HWND& { return handle; }
	void SetHandle(const HWND& handle) { this->handle = handle; }

	auto GetText(const int& dlg_item) const -> const std::string;

public:
	class Tool* const tool = nullptr;
	HINSTANCE instance = nullptr;
	HWND parent_handle = nullptr;
	HWND handle = nullptr;

public:
	static BOOL CALLBACK Dlg_WndProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

public:
	BOOL CALLBACK Dlg_WndProc_MapEditor_Init(class window* const base_win,
		HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
};