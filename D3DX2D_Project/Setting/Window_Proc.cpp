#include "stdafx.h"
#include "Window.h"


LRESULT window::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	window* win = nullptr;

	if (iMsg == WM_COMMAND || iMsg == WM_PAINT)
	{
		win = (window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		if (!win)
			return 0;
	}


	switch (iMsg)
	{
	case WM_PAINT:
	{
		break;
	}

	case WM_COMMAND:
	{
		//switch (LOWORD(wParam))
		//{
		//default:
		//	break;
		//}
		break;
	}
		

	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default :
		return DefWindowProc(hWnd, iMsg, wParam, lParam);
	}

	return 0;
}
