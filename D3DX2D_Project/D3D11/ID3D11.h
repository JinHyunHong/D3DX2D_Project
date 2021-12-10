#pragma once
#include "stdafx.h"

class ID3D11
{
public:
	ID3D11(class D3D11_Base* const base);
	
	virtual ~ID3D11() = default;

	auto GetID() const { return id; }
	void SetID(const uint& id) { this->id = id; }

private:
	uint id = 0;

protected:
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* device_context = nullptr;
};