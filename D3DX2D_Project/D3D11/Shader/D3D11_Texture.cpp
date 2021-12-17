#include "stdafx.h"
#include "D3D11_Texture.h"


D3D11_Texture::D3D11_Texture(class D3D11_Base* const base) :
	D3D11(base)
{
}

D3D11_Texture::~D3D11_Texture()
{
	Clear();
}

void D3D11_Texture::Create(const std::string& path)
{
	if (path.empty())
		assert(false);

	auto h_result = D3DX11CreateShaderResourceViewFromFileA(device, path.c_str(), nullptr, nullptr, &resource, nullptr);
	assert(SUCCEEDED(h_result));
}

void D3D11_Texture::Clear()
{
	SAFE_RELEASE(resource);
}
