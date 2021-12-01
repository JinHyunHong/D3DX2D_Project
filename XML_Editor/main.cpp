#include "stdafx.h"
#include "Header/Window.h"
#include "Core/Core.h"

int APIENTRY WinMain(HINSTANCE Inst, HINSTANCE PrevInst, LPSTR lpszCmdParam, int nCmdShow)
{
	Window::Create(Inst, 1000, 1000);
	Window::Show();

	Core::GetInst().SetWindowHandle(Window::handle);
	Core::GetInst().SetInstance(Window::instance);
	Core::GetInst().SetClientWidth(Window::GetWidth());
	Core::GetInst().SetClientHegiht(Window::GetHeight());

	while (Window::Update())
	{
		
	}

	Window::Destroy();
}