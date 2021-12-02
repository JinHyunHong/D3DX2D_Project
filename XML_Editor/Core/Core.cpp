#include "../stdafx.h"
#include "Core.h"

Core::Core()
{

}

Core::~Core()
{
	Destroy();
}

const bool Core::Initalize(const HINSTANCE& instance, const uint& width, const uint& height)
{
	this->instance = instance;
	this->width = width;
	this->height = height;

	Create();
	Show();

	return true;
}


LRESULT CALLBACK Core::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hWnd, iMsg, wParam, lParam);
	}

	return 0;
}

const bool Core::Create()
{
	WNDCLASSEX WndClassEx;

	WndClassEx.cbClsExtra = 0;
	WndClassEx.cbWndExtra = 0;
	WndClassEx.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	WndClassEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
	WndClassEx.hIcon = LoadIcon(nullptr, IDI_ERROR);
	WndClassEx.hIconSm = LoadIcon(nullptr, IDI_ERROR);
	WndClassEx.hInstance = instance;
	WndClassEx.lpfnWndProc = WndProc;
	WndClassEx.lpszClassName = L"XML_Editor";
	WndClassEx.lpszMenuName = nullptr;
	WndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	WndClassEx.cbSize = sizeof(WNDCLASSEX);

	assert(RegisterClassEx(&WndClassEx) != 0);
	handle = CreateWindowExW(WS_EX_APPWINDOW, L"XML_Editor", L"XML_Editor", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, static_cast<int>(width), static_cast<int>(height), nullptr, nullptr, instance, nullptr);

	if (!handle)
	{
		assert(false);
		return false;
	}

	return true;
}

const bool Core::Update()
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

void Core::Show()
{
	SetForegroundWindow(handle);
	SetFocus(handle);
	ShowCursor(TRUE);
	ShowWindow(handle, SW_NORMAL);
	UpdateWindow(handle);
}

void Core::Destroy()
{
	DestroyWindow(handle);
	UnregisterClass(L"XML_Editor", instance);
}