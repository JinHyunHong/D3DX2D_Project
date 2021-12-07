#include "stdafx.h"
#include "Window.h"
#include "Dialog.h"


LRESULT window::WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	window* win = nullptr;

	if (iMsg == WM_COMMAND)
	{
		win = (window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		if (!win)
			return 0;
	}


	switch (iMsg)
	{
	case WM_COMMAND:
	{
		Context* context = win->tool->GetManager<SubsystemManager>()->GetSubsystem_raw<Context>();
		switch (LOWORD(wParam))
		{
		case ID_NEW_FILE:
		{
			context->Destroy();
			win->EraseTextsWindow();
		}
		break;
		case ID_ADD_ELEMENT:
		{
			win->CreateInDialog(Dialog_type::AddElement, IDD_ELEMENT_DIALOG);
			break;
		}
		case ID_ADD_ATTRIBUTE:
		{
			win->CreateInDialog(Dialog_type::AddAttribute, IDD_ATTRIBUTE_DIALOG);
			break;
		}

		case ID_LOAD_FILE:
		{
			OPENFILENAMEA ofn;
			char file_name[256]{ 0, };
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = win->handle;
			ofn.lpstrFilter = "XML Files(*.xml)\0*.xml\0";
			ofn.lpstrFile = file_name;
			ofn.nMaxFile = 256;
			ofn.lpstrInitialDir = ".";
			if (GetOpenFileNameA(&ofn) != 0)
			{
				if (context->LoadFromFile(file_name))
				{
					MessageBox(win->handle, L"불러오기 완료", L"불러오기 완료", MB_OK);
					win->DrawTextWindow(context->ToString());
				}
				else
					MessageBox(win->handle, L"불러오기 실패", L"불러오기 실패", MB_OK);
			}


			break;
		}

		case ID_SAVE_FILE:
		{
			OPENFILENAMEA sfn;
			char file_name[256]{0,};
			ZeroMemory(&sfn, sizeof(OPENFILENAME));
			sfn.lStructSize = sizeof(OPENFILENAME);
			sfn.hwndOwner = win->handle;
			sfn.lpstrFilter = "XML Files(*.xml)\0*.xml\0";
			sfn.lpstrFile = file_name;
			sfn.nMaxFile = 256;
			sfn.lpstrInitialDir = ".";
			if (GetSaveFileNameA(&sfn) != 0)
			{
				if (context->SaveToFile(file_name))
				{
					MessageBox(win->handle, L"저장완료", L"저장완료", MB_OK); 
					win->DrawTextWindow(context->ToString());
				}
				else
					MessageBox(win->handle, L"저장실패", L"저장실패", MB_OK);
			}
			break;
		}

		}
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
