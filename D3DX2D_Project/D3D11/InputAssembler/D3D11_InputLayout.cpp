#include "stdafx.h"
#include "D3D11_InputLayout.h"

D3D11_InputLayout::D3D11_InputLayout(class D3D11_Base* const base) :
	ID3D11(base)
{
}

D3D11_InputLayout::~D3D11_InputLayout()
{
	Clear();
}

void D3D11_InputLayout::Create(D3D11_INPUT_ELEMENT_DESC* descs, const uint& count, ID3DBlob* blob)
{
	if (descs || !count || !blob)
		assert(false);

	auto h_result = device->CreateInputLayout(descs, count, blob->GetBufferPointer(), blob->GetBufferSize(), &input_layout);
	assert(SUCCEEDED(h_result));
}

void D3D11_InputLayout::Clear()
{
	SAFE_RELEASE(input_layout);
}