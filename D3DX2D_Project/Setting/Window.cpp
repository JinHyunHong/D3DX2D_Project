#include "stdafx.h"
#include "window.h"
#include "Dialog.h"

window::window(Tool* const tool, 
	const HINSTANCE& instance,
	const uint& width, const uint& height) :
	tool(tool),
	instance(instance),
	width(width),
	height(height)
{
}

window::~window()
{
	Destroy();
}

const bool window::Initialize()
{
	return true;
}

void window::DrawTextWindow(const std::string& text)
{
	PAINTSTRUCT ps;
	RECT rect{ 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
	HDC hdc = BeginPaint(handle, &ps);
	DrawTextA(hdc, text.c_str(), text.length(), &rect, DT_WORDBREAK);
	EndPaint(handle, &ps);
}

void window::EraseTextsWindow()
{
	RECT rect{ 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
	InvalidateRect(handle, &rect, TRUE);
}


const bool window::Create(const wchar_t* class_name, const wchar_t* window_name)
{
	WNDCLASSEX WndClassEx;

	WndClassEx.cbClsExtra = 0;
	WndClassEx.cbWndExtra = sizeof(window*);
	WndClassEx.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	WndClassEx.hCursor = LoadCursor(instance, IDC_ARROW);
	WndClassEx.hIcon = LoadIcon(instance, IDI_ERROR);
	WndClassEx.hIconSm = LoadIcon(instance, IDI_ERROR);
	WndClassEx.hInstance = instance;
	WndClassEx.lpszMenuName = nullptr;
	WndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	WndClassEx.cbSize = sizeof(WNDCLASSEXA);		
	WndClassEx.lpszClassName = class_name;
	WndClassEx.lpfnWndProc = WndProc;
	assert(RegisterClassEx(&WndClassEx) != 0);
	handle = CreateWindowEx(WS_EX_APPWINDOW, class_name, window_name, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, static_cast<int>(width), static_cast<int>(height), nullptr, nullptr, instance, nullptr);

	if (!handle)
	{
		assert(false);
		return false;
	}

	SetWindowLongPtr(handle, GWL_USERDATA, (LONG)this);

	return true;
}

const bool window::Update()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.message != WM_QUIT;
}

void window::Show()
{
	RECT rc = { 0, 0, static_cast<long>(width), static_cast<long>(height) };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(handle, HWND_TOPMOST, 100, 100, rc.right - rc.left,
		rc.bottom - rc.top, SWP_NOMOVE | SWP_NOZORDER);
	SetForegroundWindow(handle);
	SetFocus(handle);
	ShowCursor(TRUE);
	ShowWindow(handle, SW_NORMAL);
	UpdateWindow(handle);
}

void window::Destroy()
{
	DestroyWindow(handle);
	UnregisterClass(L"XML_Editor", instance);
}

auto window::GetDialog(const Dialog_type& type)
{
	assert(dialogs.find(type) != dialogs.end());

	return dialogs[type];
}

auto window::GetDialog(const HWND& handle) const -> const std::shared_ptr<class Dialog>
{
	for (const auto& dialog : dialogs)
	{
		if (dialog.second->GetHandle() == handle)
			return dialog.second;
	}

	return nullptr;
}

void window::CreateInDialog(const Dialog_type& type, const int& resource_id)
{
	std::shared_ptr<Dialog> dialog = std::make_shared<Dialog>(tool);
	dialogs[type] = dialog;
	dialog->Initialize(instance, handle, resource_id);
}

void window::AddDialogHandle(const Dialog_type& type, const HWND& handle)
{
	if (type == Dialog_type::Unknown || !handle)
	{
		assert(false);
		return;
	}

	dialogs[type]->SetHandle(handle);
}


auto window::GetDialogEmptyHandle() const -> const Dialog_type
{
	for (const auto& dialog : dialogs)
	{
		if (!dialog.second->GetHandle())
			return dialog.first;
	}
	return Dialog_type::Unknown;
}

auto window::GetDialogType(const std::shared_ptr<class Dialog>& ref_dialog) const -> const Dialog_type
{
	for (const auto& dialog : dialogs)
	{
		if (dialog.second == ref_dialog)
			return dialog.first;
	}
	return Dialog_type::Unknown;
}