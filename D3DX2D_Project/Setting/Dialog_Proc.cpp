#include "stdafx.h"
#include "Dialog.h"
#include "Core/Core.h"
#include "Manager/SubsystemManager.h"
#include "Scene/MapEditorScene.h"


BOOL Dialog::Dlg_WndProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HWND parent_handle = GetParent(hDlg);

	window* base_win = (window*)GetWindowLongPtr(parent_handle, GWLP_USERDATA);

	if (!parent_handle || !base_win)
	{
		assert(false);
		return 0;
	}

	switch (iMsg)
	{
	case WM_INITDIALOG:
	{
		Dialog_type type = base_win->GetDialogEmptyHandle();
		base_win->AddDialogHandle(type, hDlg);
		break;
	}
	default:
		break;
	}

	std::shared_ptr<Dialog> dialog = base_win->GetDialog(hDlg);

	switch (base_win->GetDialogType(dialog))
	{
	case Dialog_type::Unknown:
		break;
	case Dialog_type::MapEditorInit:
		dialog->Dlg_WndProc_MapEditor_Init(base_win, hDlg, iMsg, wParam, lParam);
		break;
	default:
		break;
	}

	return 0;
};

BOOL Dialog::Dlg_WndProc_MapEditor_Init(window* const base_win, HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_INITDIALOG:
	{
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_MAP_EDITOR_INIT_OK:
		{
			std::string width_text = GetText(IDC_MAP_EDITOR_INIT_WIDTH);
			std::string height_text = GetText(IDC_MAP_EDITOR_INIT_HEIGHT); 

			auto map_editor = tool->GetManager<SubsystemManager>()->GetSubsystem<SceneManager>()->GetScene<MapEditorScene>("MapEditor");
			map_editor->CreateTiles("", nullptr, std::stof(width_text), std::stof(height_text));
			
			base_win->EraseTextsWindow();

			EndDialog(hDlg, 0);
			break;
		}
		case IDC_MAP_EDITOR_INIT_CANCLE:
			EndDialog(hDlg, 0);
			break;
		}
		break;
	}
	case WM_DESTROY:
	case WM_CLOSE:
	{
		EndDialog(hDlg, 0);
		break;
	}
	}		
	return 0;
}