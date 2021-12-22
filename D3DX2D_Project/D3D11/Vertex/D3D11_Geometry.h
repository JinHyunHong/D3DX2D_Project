#pragma once
#include "stdafx.h"

template<typename T>
class D3D11_Geometry
{
public:
	D3D11_Geometry() = default;
	virtual ~D3D11_Geometry();

	// Vertices
	auto GetVertexCount() const { return static_cast<uint>(vertices.size()); }
	auto GetVertexPointer() const { return vertices.data(); }
	auto GetVertexByteWidth() const { return GetVertexCount() * sizeof(T); }
	auto GetVertices() const -> const std::vector<T>& { return vertices; }
	auto GetVertices(const uint& offset, const uint& count) -> const std::vector<T>;
	void AddVertex(const T& vertex);
	void AddVertices(const std::vector<T>& vertices);
	void SetVertices(const std::vector<T>& vertices);

	// Indices
	auto GetIndexCount() const { return static_cast<uint>(indices.size()); }
	auto GetIndexPointer() const { return vertices.data(); }
	auto GetIndexByteWidth() const { return GetIndexCount() * sizeof(uint); }
	auto GetIndices() const -> const std::vector<uint>& { return indices; }
	auto GetIndices(const uint& offset, const uint& count) -> const std::vector<uint>;
	void AddIndex(const uint& index);
	void AddIndices(const std::vector<uint>& indices);
	void Setindices(const std::vector<uint>& indices);

	void Clear();
private:
	std::vector<T> vertices;
	std::vector<uint> indices;
};

class Geometry_Generator final
{
public:
	static void CreateQuad(D3D11_Geometry<struct D3D11_VertexTexture>& geometry);
	static void CreateQuad(D3D11_Geometry<struct D3D11_VertexColor>& geometry, const D3DXCOLOR& color);
};

#include "D3D11_Geometry.inl"