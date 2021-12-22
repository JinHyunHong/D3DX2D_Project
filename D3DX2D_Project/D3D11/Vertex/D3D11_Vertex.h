#pragma once

struct D3D11_VertexColor
{
	D3DXVECTOR3 position;
	D3DXCOLOR color;

	static const uint count = 2;

	static D3D11_INPUT_ELEMENT_DESC descs[];

	D3D11_VertexColor(const D3DXVECTOR3& position, const D3DXCOLOR& color)
		: position(position), color(color)
	{
		{}
	}
};

struct D3D11_VertexTexture
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 uv;

	static const uint count = 2;

	static D3D11_INPUT_ELEMENT_DESC descs[];

	D3D11_VertexTexture()
		: position(0, 0, 0),
		uv(0, 0)
	{}

	D3D11_VertexTexture(const D3DXVECTOR3& position, const D3DXVECTOR2& uv)
		: position(position), uv(uv)
	{}
};
