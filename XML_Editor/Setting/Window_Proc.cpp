#include "stdafx.h"
#include "Window.h"

LRESULT CALLBACK window::MainWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT CALLBACK window::SubLeftWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT CALLBACK window::SubRightWndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
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



