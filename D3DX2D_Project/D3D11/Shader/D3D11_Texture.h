#pragma once

class D3D11_Texture final :
	public D3D11
{
public:
	D3D11_Texture(class D3D11_Base* const base);
	~D3D11_Texture();

	auto GetResource() const -> const ID3D11ShaderResourceView* { return resource; }
	void Create(const std::string& path);
	void Clear();

private:
	ID3D11ShaderResourceView* resource = nullptr;
};