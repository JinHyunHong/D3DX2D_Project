#pragma once


class D3D11_IndexBuffer final :
	public D3D11
{
public:
	D3D11_IndexBuffer(class D3D11_Base* const base);
	~D3D11_IndexBuffer();

	auto Create(const std::vector<uint> indices, const D3D11_USAGE& usage = D3D11_USAGE_IMMUTABLE);
	void Clear();

	auto GetResource() const -> ID3D11Buffer* { return buffer; }
	auto GetStride() const -> const uint& { return stride; }
	auto GetOffset() const -> const uint& { return offset; }
	auto GetCount() const -> const uint& { return count; }

private:
	ID3D11Buffer* buffer = nullptr;
	uint stride = 0;
	uint offset = 0;
	uint count = 0;
};

