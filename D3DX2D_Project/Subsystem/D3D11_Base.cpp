#include "stdafx.h"
#include "D3D11_Base.h"

D3D11_Base::D3D11_Base(class Tool* const tool) :
	ISubsystem(tool)
{
}

D3D11_Base::~D3D11_Base()
{
}

bool D3D11_Base::Initialize()
{
	return true;
}

void D3D11_Base::Update()
{
}

void D3D11_Base::Destroy()
{
}

void D3D11_Base::CreateBackBuffer()
{
}

void D3D11_Base::Begin()
{
}

void D3D11_Base::End()
{
}
