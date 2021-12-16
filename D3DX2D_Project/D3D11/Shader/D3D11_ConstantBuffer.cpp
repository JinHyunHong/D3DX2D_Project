#include "stdafx.h"
#include "D3D11_ConstantBuffer.h"

D3D11_ConstnatBuffer::D3D11_ConstnatBuffer(D3D11_Base* const base) :
	ID3D11(base)
{
}

D3D11_ConstnatBuffer::~D3D11_ConstnatBuffer()
{
	Clear();
}

void D3D11_ConstnatBuffer::Clear()
{
	SAFE_RELEASE(buffer);
}

bool D3D11_ConstnatBuffer::Unmap()
{
	if (!buffer)
		return false;

	device_context->Unmap(buffer, 0);
	return false;
}
