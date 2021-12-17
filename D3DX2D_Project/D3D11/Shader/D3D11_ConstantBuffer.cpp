#include "stdafx.h"
#include "D3D11_ConstantBuffer.h"

D3D11_ConstantBuffer::D3D11_ConstantBuffer(D3D11_Base* const base) :
	D3D11(base)
{
}

D3D11_ConstantBuffer::~D3D11_ConstantBuffer()
{
	Clear();
}

void D3D11_ConstantBuffer::Clear()
{
	SAFE_RELEASE(buffer);
}

bool D3D11_ConstantBuffer::Unmap()
{
	if (!buffer)
		return false;

	device_context->Unmap(buffer, 0);
	return false;
}
