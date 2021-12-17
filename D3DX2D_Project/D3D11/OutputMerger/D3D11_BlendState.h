#pragma once

class D3D11_BlendState final :
	public D3D11
{
public:
	D3D11_BlendState(class D3D11_Base* const base);
	~D3D11_BlendState();

	auto GetResource() const -> ID3D11BlendState* { return state; }
	auto GetBlendFactor() const { return factor; }
	auto GetSamplerMask() const { return mask; }

	void Create
	(
		const bool& is_blend_enabled, 
		const D3D11_BLEND& src_blend = D3D11_BLEND_SRC_ALPHA,
		const D3D11_BLEND& dest_blend = D3D11_BLEND_INV_SRC_ALPHA, 
		const D3D11_BLEND_OP blend_op = D3D11_BLEND_OP_ADD,
		const D3D11_BLEND& src_blend_alpha = D3D11_BLEND_ONE,
		const D3D11_BLEND& dest_blend_alpha = D3D11_BLEND_ZERO, 
		const D3D11_BLEND_OP blend_op_alpha = D3D11_BLEND_OP_ADD, 
		const float& factor = 0.0f, 
		const D3D11_COLOR_WRITE_ENABLE& color_mask = D3D11_COLOR_WRITE_ENABLE_ALL
	);
	void Clear();

private:
	ID3D11BlendState* state = nullptr;
	float factor = 0.0f;
	uint mask = 0xffffffff;
};