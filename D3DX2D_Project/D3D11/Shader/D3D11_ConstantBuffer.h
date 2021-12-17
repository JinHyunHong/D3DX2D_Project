#pragma once

class D3D11_ConstnatBuffer final :
	public D3D11
{
public:
	D3D11_ConstnatBuffer(class D3D11_Base* const base);
	~D3D11_ConstnatBuffer();

	auto GetResource() const -> const ID3D11Buffer* { return buffer; }

	template<typename T>
	void Create(const D3D11_USAGE& usage = D3D11_USAGE_DYNAMIC);
	void Clear();

	template<typename T>
	auto Map()->T*;
	bool Unmap();

private:
	ID3D11Buffer* buffer = nullptr;
};

template<typename T>
inline void D3D11_ConstnatBuffer::Create(const D3D11_USAGE& usage)
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = sizeof(T);
	desc.Usage = usage;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

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

	auto h_reslut = device->CreateBuffer(&desc, nullptr, &buffer);
	assert(SUCCEEDED(h_reslut));
}

template<typename T>
inline auto D3D11_ConstnatBuffer::Map() -> T*
{
	D3D11_MAPPED_SUBRESOURCE sub_resource;

	auto h_reslut = device_context->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub_resource);
	return static_cast<T*>(sub_resource.pData);
}
