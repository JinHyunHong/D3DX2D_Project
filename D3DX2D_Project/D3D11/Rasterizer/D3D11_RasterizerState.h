#pragma once

class D3D11_RasterizerState final :
	public ID3D11
{
public:
	D3D11_RasterizerState(class D3D11_Base* const base);
	~D3D11_RasterizerState();

	auto GetResource() const -> const ID3D11RasterizerState* { return state; }

	void Create(const D3D11_CULL_MODE& cull_mode, const D3D11_FILL_MODE& fill_mode);
	void Clear();

private:
	ID3D11RasterizerState* state = nullptr;
};