#include "stdafx.h"
#include "Dialog.h"
#include "Core/Core.h"
#include "Subsystem/Context.h"
#include "Manager/SubsystemManager.h"


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
	case Dialog_type::AddElement:
		dialog->Dlg_WndProc_AddElement(base_win, hDlg, iMsg, wParam, lParam);
		break;
	case Dialog_type::AddAttribute:
		dialog->Dlg_WndProc_AddAttribute(base_win, hDlg, iMsg, wParam, lParam);
		break;
	default:
		break;
	}

	return 0;
};

BOOL Dialog::Dlg_WndProc_AddElement(window* const base_win, HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
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
		case ID_ELEMENT_OK:
		{
			std::string new_text = GetText(IDC_EDIT_ELEMENT_NEW);
			std::string base_text = GetText(IDC_EDIT_ELEMENT_BASE);

			Context* context = tool->GetManager<SubsystemManager>()->GetSubsystem_raw<Context>();
			context->AddElement(new_text, base_text);
			base_win->EraseTextsWindow();

			EndDialog(hDlg, 0);
			break;
		}
		case ID_ELEMENT_CANCEL:
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
BOOL Dialog::Dlg_WndProc_AddAttribute(window* const base_win, HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
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
		case ID_ATTRIBUTE_OK:
		{
			Context* context = tool->GetManager<SubsystemManager>()->GetSubsystem_raw<Context>();
			std::string base_text = GetText(IDC_EDIT_ATTRIBUTE_BASE);
			std::string new_text = GetText(IDC_EDIT_ATTRIBUTE_NEW);
			std::string value_text = GetText(IDC_EDIT_ATTRIBUTE_VALUE);

			std::string type = context->DeduceTextType(value_text);

			if(type == "float")
				context->AddAttribute<float>(base_text, new_text, std::stof(value_text));
			else if(type == "int")
				context->AddAttribute<int>(base_text, new_text, std::stoi(value_text));
			else
				context->AddAttribute<const char*>(base_text, new_text, value_text.c_str());

			base_win->EraseTextsWindow();

			EndDialog(hDlg, 0);
			break;
		}
		case ID_ATTRIBUTE_CANCEL:
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
;