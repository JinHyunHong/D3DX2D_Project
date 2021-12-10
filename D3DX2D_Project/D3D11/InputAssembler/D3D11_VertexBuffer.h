#pragma once

class D3D11_VertexBuffer final :
	public ID3D11
{
public:
	D3D11_VertexBuffer(class D3D11_Base* const base);
	~D3D11_VertexBuffer();

	template<typename T>
	auto Create(const std::vector<T>& vertices, const D3D11_USAGE& usage = D3D11_USAGE_IMMUTABLE);
	void Clear();

	auto GetStride() const -> const uint& { return stride; }
	auto GetOffset() const -> const uint& { return offset; }
	auto GetCount() const -> const uint& { return count; }

private:
	ID3D11Buffer* buffer = nullptr;
	uint stride = 0;
	uint offset = 0;
	uint count = 0;
};

template<typename T>
inline auto D3D11_VertexBuffer::Create(const std::vector<T>& vertices, const D3D11_USAGE& usage)
{
	stride = sizeof(T);
	count = static_cast<uint>(vertices.size());

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.ByteWidth = stride * count;
	desc.Usage = usage;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

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
	sub_resource.pSysMem = vertices.data();

	auto h_result = device->CreateBuffer(&desc, &sub_resource, &buffer);
	assert(SUCCEEDED(h_result));
}
