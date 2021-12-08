#include "stdafx.h"
#include "window.h"

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
