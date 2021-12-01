#pragma once
#include "../stdafx.h"

namespace Window
{
	static HINSTANCE instance;
	static HWND handle = nullptr;

	inline LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (iMsg)
		{
		case WM_CLOSE:
		case WM_DESTROY:
			PostQuitMessage(0);
		default:
			DefWindowProc(hWnd, iMsg, wParam, lParam);
		}

		return 0;
	}

	inline bool Create(HINSTANCE hInst, const uint& width, const uint& height)
	{
		instance = hInst;

		WNDCLASSEX WndClassEx;

		WndClassEx.cbSize = sizeof(WNDCLASSEX);
		WndClassEx.lpfnWndProc = WndProc;
		WndClassEx.cbClsExtra = 0;
		WndClassEx.cbWndExtra = 0;
		WndClassEx.hInstance = instance;
		WndClassEx.hIcon = LoadIcon(instance, IDI_ERROR);
		WndClassEx.hIconSm = LoadIcon(instance, IDI_ERROR);
		WndClassEx.hCursor = LoadCursor(nullptr, IDC_ARROW);
		WndClassEx.hbrBackground = (HBRUSH)(WHITE_BRUSH);
		WndClassEx.lpszMenuName = nullptr;
		WndClassEx.lpszClassName = L"XML_Editor";
		WndClassEx.style = CS_HREDRAW | CS_VREDRAW;

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

	inline float GetWidth()
	{
		RECT rect;
		GetClientRect(handle, &rect);
		return static_cast<float>(rect.right - rect.left);
	}

	inline float GetHeight()
	{
		RECT rect;
		GetClientRect(handle, &rect);
		return static_cast<float>(rect.bottom - rect.top);
	}
	
	inline const bool Update()
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

	inline void Show()
	{
		SetForegroundWindow(handle);
		SetFocus(handle);
		ShowCursor(true);
		ShowWindow(handle, 0);
		UpdateWindow(handle);
	}

	inline void Destroy()
	{
		DestroyWindow(handle);
		UnregisterClass(L"XML_Editor", instance);
	}
}