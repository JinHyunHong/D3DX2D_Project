#include "D3D11_Geometry.h"

template<typename T>
inline D3D11_Geometry<T>::~D3D11_Geometry()
{
	Clear();
}

template<typename T>
inline auto D3D11_Geometry<T>::GetVertices(const uint& offset, const uint& count) -> const std::vector<T>
{
	std::vector<T> sub_vertices;
	auto first = vertices.begin() + offset;
	auto last = first + count;

	sub_vertices = vertices.assign(first, last);

	return sub_vertices;
}

template<typename T>
inline void D3D11_Geometry<T>::AddVertex(const T& vertex)
{
	vertices.emplace_back(vertex);
}

template<typename T>
inline void D3D11_Geometry<T>::AddVertices(const std::vector<T>& vertices)
{
	this->vertices.insert(this->vertices.end(), vertices.begin(), vertices.end());
}

template<typename T>
inline void D3D11_Geometry<T>::SetVertices(const std::vector<T>& vertices)
{
	CLEAR_VECTOR(this->vertices);
	this->vertices(vertices);
}

template<typename T>
inline auto D3D11_Geometry<T>::GetIndices(const uint& offset, const uint& count) -> const std::vector<uint>
{
	std::vector<uint> sub_indices;
	auto first = indices.begin() + offset;
	auto last = first + count;

	sub_indices = indices.assign(first, last);

	return sub_indices;
}

template<typename T>
inline void D3D11_Geometry<T>::AddIndex(const uint& index)
{
	indices.emplace_back(index);
}

template<typename T>
inline void D3D11_Geometry<T>::AddIndices(const std::vector<uint>& indices)
{
	this->indices.insert(this->indices.end(), indices.begin(), indices.end());
}

template<typename T>
inline void D3D11_Geometry<T>::Setindices(const std::vector<uint>& indices)
{
	CLEAR_VECTOR(this->indices);
	this->indices(indices);
}

template<typename T>
inline void D3D11_Geometry<T>::Clear()
{
	CLEAR_VECTOR(vertices); 
	CLEAR_VECTOR(indices);
}
