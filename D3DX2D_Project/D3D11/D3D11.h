#pragma once
#include "stdafx.h"

class D3D11 : 
	public Object
{
public:
	D3D11(class D3D11_Base* const base);
	virtual ~D3D11() = default;

protected:
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* device_context = nullptr;
};