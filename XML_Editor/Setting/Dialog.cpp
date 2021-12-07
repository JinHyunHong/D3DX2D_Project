#include "stdafx.h"
#include "Dialog.h"

Dialog::Dialog(Tool* const tool) :
	tool(tool)
{
}

bool Dialog::Initalize(HINSTANCE instance, HWND parent_handle, const int& Resource_id)
{
	this->instance = instance;
	this->parent_handle = parent_handle;
	DialogBox(instance, MAKEINTRESOURCE(Resource_id), parent_handle, Dlg_WndProc);
	return true;
}

auto Dialog::GetText(const int& dlg_item) const -> const std::string
{
	char dlg_text[128]{0,};
	GetDlgItemTextA(handle, dlg_item, dlg_text, 128);

	return std::string(dlg_text);
}
