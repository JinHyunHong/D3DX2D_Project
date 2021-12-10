#pragma once
#include "stdafx.h"

struct D3D11_VertexTexture
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 uv;

	D3D11_INPUT_ELEMENT_DESC desc[];

	D3D11_VertexTexture()
		: position(0, 0, 0),
		uv(0, 0)
	{}

	D3D11_VertexTexture(const D3DXVECTOR3& position, const D3DXVECTOR2& uv)
		: position(position), uv(uv)
	{}
};

struct D3D11_VertexColor
{
	D3DXVECTOR3 position;
	D3DXCOLOR color;

	D3D11_INPUT_ELEMENT_DESC desc[];
	
	D3D11_VertexColor(const D3DXVECTOR3& position, const D3DXCOLOR& color)
		: position(position), color(color)
	{
		{}
	}
};

template<typename T>
class D3D11_Geometry
{

};