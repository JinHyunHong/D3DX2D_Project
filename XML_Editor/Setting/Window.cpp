#include "../stdafx.h"
#include "window.h"

window::window(const WindowSplitType& type, const HINSTANCE& instance, 
	const uint& width, const uint& height) :
	type(type),
	instance(instance),
	width(width),
	height(height)
{
}

window::~window()
{
	Destroy();
}

const bool window::Initalize()
{
	return true;
}

auto window::GetChild(const WindowSplitType& type) -> std::shared_ptr<window>
{
	for (const auto& child : childs)
	{
		if (child->GetType() == type)
			return child;
	}
	return nullptr;
}

void window::AddChild(const std::shared_ptr<window>& child)
{
	if (!child)
		return;

	if (GetChild(child->GetType()))
		return;

	childs.emplace_back(child);
}

const bool window::Create()
{
	WNDCLASSEX WndClassEx;
	
	WndClassEx.cbClsExtra = 0;
	WndClassEx.cbWndExtra = 0;
	WndClassEx.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	WndClassEx.hCursor = LoadCursor(instance, IDC_ARROW);
	WndClassEx.hIcon = LoadIcon(instance, MAKEINTRESOURCE(IDI_ICON1));
	WndClassEx.hIconSm = LoadIcon(instance, MAKEINTRESOURCE(IDI_ICON1));
	WndClassEx.hInstance = instance;
	WndClassEx.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	WndClassEx.cbSize = sizeof(WNDCLASSEX);

	switch (type)
	{
	case WindowSplitType::Unknown:
	{
		assert(false);
		return false;
	}
	case WindowSplitType::Main:
	{
		WndClassEx.lpszClassName = L"XML_Editor";
		WndClassEx.lpfnWndProc = MainWndProc;
		assert(RegisterClassEx(&WndClassEx) != 0);
		handle = CreateWindowExW(WS_EX_APPWINDOW, L"XML_Editor", L"XML_Editor", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
			CW_USEDEFAULT, static_cast<int>(width), static_cast<int>(height), nullptr, nullptr, instance, nullptr);
		break;
	}
	case WindowSplitType::Left:
	{
		if (!parent)
		{
			assert(false);
			return false;
		}
		RECT rect;
		GetClientRect(parent->GetWindowHandle(), &rect);
		WndClassEx.lpszClassName = L"left";
		WndClassEx.lpfnWndProc = SubLeftWndProc;
		assert(RegisterClassEx(&WndClassEx) != 0);
		handle = CreateWindowExW(WS_EX_CLIENTEDGE, L"left", L"left",
			WS_CHILD | WS_VISIBLE, rect.left, rect.top,
			(rect.right - rect.left) / 2, (rect.bottom - rect.top), parent->GetWindowHandle(), NULL,
			instance, NULL);
		break;
	}
	case WindowSplitType::Right:
	{
		if (!parent)
		{
			assert(false);
			return false;
		}
		RECT rect;
		GetClientRect(parent->GetWindowHandle(), &rect);
		WndClassEx.lpszClassName = L"right";
		WndClassEx.lpfnWndProc = SubRightWndProc;
		assert(RegisterClassEx(&WndClassEx) != 0);
		handle = CreateWindowExW(WS_EX_CLIENTEDGE, L"right", L"right",
			WS_CHILD | WS_VISIBLE, rect.right / 2, rect.top,
			(rect.right - rect.left) / 2, (rect.bottom - rect.top), parent->GetWindowHandle(), NULL,
			instance, NULL);
		break;
	}
	}

	if (!handle)
	{
		assert(false);
		return false;
	}

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

