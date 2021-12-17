#include "stdafx.h"
#include "D3D11_BlendState.h"

D3D11_BlendState::D3D11_BlendState(D3D11_Base* const base) :
	D3D11(base)
{
}

D3D11_BlendState::~D3D11_BlendState()
{
	Clear();
}

void D3D11_BlendState::Create(const bool& is_blend_enabled, const D3D11_BLEND& src_blend, const D3D11_BLEND& dest_blend, 
	const D3D11_BLEND_OP blend_op, const D3D11_BLEND& src_blend_alpha, const D3D11_BLEND& dest_blend_alpha, 
	const D3D11_BLEND_OP blend_op_alpha, const float& factor, const D3D11_COLOR_WRITE_ENABLE& color_mask)
{
	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable = is_blend_enabled;
	desc.RenderTarget[0].SrcBlend = src_blend;
	desc.RenderTarget[0].DestBlend = dest_blend;
	desc.RenderTarget[0].BlendOp = blend_op;
	desc.RenderTarget[0].SrcBlendAlpha = src_blend_alpha;
	desc.RenderTarget[0].DestBlendAlpha = dest_blend_alpha;
	desc.RenderTarget[0].BlendOpAlpha = blend_op_alpha;
	desc.RenderTarget[0].RenderTargetWriteMask = color_mask;
	this->factor = factor;

	auto h_result = device->CreateBlendState(&desc, &state);
	assert(SUCCEEDED(h_result));
}

void D3D11_BlendState::Clear()
{
	SAFE_RELEASE(state);
	factor = 0.0f;
	mask = 0xffffffff;
}
