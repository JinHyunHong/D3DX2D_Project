#include "stdafx.h"
#include "Core/Core.h"

int APIENTRY WinMain(HINSTANCE Inst, HINSTANCE PrevInst, LPSTR lpszCmdParam, int nCmdShow)
{
	Core::GetInst().Initialize(Inst, 800, 500);

	while (Core::GetInst().Update())
	{
		Core::GetInst().Render();
	}

	Core::GetInst().Destroy();
}