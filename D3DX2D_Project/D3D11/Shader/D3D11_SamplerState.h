#pragma once

class D3D11_SamplerState final :
	public D3D11
{
public:
	D3D11_SamplerState(class D3D11_Base* const base);
	~D3D11_SamplerState();

	auto GetResource() const -> ID3D11SamplerState* { return state; }

	void Create(const D3D11_FILTER& filter, const D3D11_TEXTURE_ADDRESS_MODE& address_mode,
		const D3D11_COMPARISON_FUNC& comparision_func = D3D11_COMPARISON_ALWAYS);
	void Clear();

private:
	ID3D11SamplerState* state = nullptr;
};