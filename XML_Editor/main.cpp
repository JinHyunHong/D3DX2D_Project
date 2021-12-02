#include "stdafx.h"
#include "Core/Core.h"

int APIENTRY WinMain(HINSTANCE Inst, HINSTANCE PrevInst, LPSTR lpszCmdParam, int nCmdShow)
{
	Core::GetInst().Initalize(Inst, 500, 500);

	while (Core::GetInst().Update())
	{
		
	}

	Core::GetInst().Destroy();
}