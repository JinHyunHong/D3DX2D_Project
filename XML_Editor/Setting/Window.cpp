#include "../stdafx.h"
#include "window.h"
#include "Dialog.h"

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
	RECT rect;
	GetClientRect(handle, &rect);
	auto hdc = GetDC(handle);
	DrawTextA(hdc, text.c_str(), text.length(), &rect, DT_WORDBREAK);
}

void window::EraseTextsWindow()
{
	RECT rect{ 0, 0, width, height };
	InvalidateRect(handle, &rect, TRUE);
}

auto window::GetDialog(const Dialog_type& type)
{
	assert(dialogs.find(type) != dialogs.end());

	return dialogs[type];
}

auto window::GetDialog(const HWND& handle) const -> const std::shared_ptr<class Dialog>
{
	for (const auto& dialog : dialogs)
	{
		if (dialog.second->GetHandle() == handle)
			return dialog.second;
	}

	return nullptr;
}

void window::CreateInDialog(const Dialog_type& type, const int& resource_id)
{
	std::shared_ptr<Dialog> dialog = std::make_shared<Dialog>(tool);
	dialogs[type] = dialog;
	dialog->Initalize(instance, handle, resource_id);
}

void window::AddDialogHandle(const Dialog_type& type, const HWND& handle)
{
	if (type == Dialog_type::Unknown || !handle)
	{
		assert(false);
		return;
	}

	dialogs[type]->SetHandle(handle);
}


auto window::GetDialogEmptyHandle() const -> const Dialog_type
{
	for (const auto& dialog : dialogs)
	{
		if (!dialog.second->GetHandle())
			return dialog.first;
	}
	return Dialog_type::Unknown;
}

auto window::GetDialogType(const std::shared_ptr<class Dialog>& ref_dialog) const -> const Dialog_type
{
	for (const auto& dialog : dialogs)
	{
		if (dialog.second == ref_dialog)
			return dialog.first;
	}
	return Dialog_type::Unknown;
}


const bool window::Create()
{
	WNDCLASSEX WndClassEx;
	
	WndClassEx.cbClsExtra = 0;
	WndClassEx.cbWndExtra = sizeof(window*);
	WndClassEx.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	WndClassEx.hCursor = LoadCursor(instance, IDC_ARROW);
	WndClassEx.hIcon = LoadIcon(instance, MAKEINTRESOURCE(IDI_ICON1));
	WndClassEx.hIconSm = LoadIcon(instance, MAKEINTRESOURCE(IDI_ICON1));
	WndClassEx.hInstance = instance;
	WndClassEx.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClassEx.style = CS_HREDRAW | CS_VREDRAW;
	WndClassEx.cbSize = sizeof(WNDCLASSEX);		
	WndClassEx.lpszClassName = L"XML_Editor";
	WndClassEx.lpfnWndProc = WndProc;
	assert(RegisterClassEx(&WndClassEx) != 0);
	handle = CreateWindowExW(WS_EX_APPWINDOW, L"XML_Editor", L"XML_Editor", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
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
