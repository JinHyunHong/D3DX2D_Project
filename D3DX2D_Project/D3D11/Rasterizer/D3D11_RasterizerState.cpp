#include "stdafx.h"
#include "D3D11_RasterizerState.h"

D3D11_RasterizerState::D3D11_RasterizerState(class D3D11_Base* const base) :
	D3D11(base)
{
}

D3D11_RasterizerState::~D3D11_RasterizerState()
{
	Clear();
}

void D3D11_RasterizerState::Create(const D3D11_CULL_MODE& cull_mode, const D3D11_FILL_MODE& fill_mode)
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_RASTERIZER_DESC));
	desc.CullMode = cull_mode;
	desc.FillMode = fill_mode;
	desc.FrontCounterClockwise = false;
	auto h_result = device->CreateRasterizerState(&desc, &state);
	assert(SUCCEEDED(h_result));
}

void D3D11_RasterizerState::Clear()
{
	SAFE_RELEASE(state);
}
