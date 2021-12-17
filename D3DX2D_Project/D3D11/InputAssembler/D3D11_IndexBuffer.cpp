#include "stdafx.h"
#include "D3D11_IndexBuffer.h"

D3D11_IndexBuffer::D3D11_IndexBuffer(D3D11_Base* const base) :
	D3D11(base)
{
}

D3D11_IndexBuffer::~D3D11_IndexBuffer()
{
	Clear();
}

auto D3D11_IndexBuffer::Create(const std::vector<uint> indices, const D3D11_USAGE& usage)
{
	stride = sizeof(uint);
	count = static_cast<uint>(indices.size());

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = stride * count;
	desc.Usage = usage;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	switch (usage)
	{
	case D3D11_USAGE_DEFAULT:
	case D3D11_USAGE_IMMUTABLE:
		desc.CPUAccessFlags = 0;
		break;
	case D3D11_USAGE_DYNAMIC:
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		break;
	case D3D11_USAGE_STAGING:
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
		break;
	}

	D3D11_SUBRESOURCE_DATA sub_resource;
	ZeroMemory(&sub_resource, sizeof(D3D11_SUBRESOURCE_DATA));
	sub_resource.pSysMem = indices.data();

	auto h_result = device->CreateBuffer(&desc, &sub_resource, &buffer);
	assert(SUCCEEDED(h_result));
}

void D3D11_IndexBuffer::Clear()
{
	SAFE_RELEASE(buffer);
	stride = 0;
	offset = 0;
	count = 0;
}
