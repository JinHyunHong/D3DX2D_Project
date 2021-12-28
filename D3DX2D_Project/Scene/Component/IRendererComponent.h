#pragma once
#include "IComponent.h"

enum class MeshType : uint
{
	Quad,
	ScreenQuad
};

class IRendererComponent :
	public IComponent
{
public:
	IRendererComponent(class Tool* const tool, class Actor* const actor,
		class TransformComponent* const transform);
	virtual ~IRendererComponent() = default;

	virtual bool Initialize() override;
	virtual void Update() = 0;
	virtual void Destroy() = 0;

	// Mesh
	auto GetVertexBuffer() const { return vertex_buffer; }
	auto GetIndexBuffer() const { return index_buffer; }
	void SetStandardMesh();

	// Material
	auto GetVertexShader() const { return vertex_shader; }
	auto GetPixelShader() const { return pixel_shader; }
	auto GetInputLayout() const { return input_layout; }
	void SetStandardMaterial();


protected:
	class D3D11_Base* base = nullptr;
	MeshType mesh_type = MeshType::Quad;
	std::shared_ptr<D3D11_VertexBuffer> vertex_buffer;
	std::shared_ptr<D3D11_IndexBuffer> index_buffer;
	std::shared_ptr<D3D11_InputLayout> input_layout;
	std::shared_ptr<D3D11_Shader> vertex_shader;
	std::shared_ptr<D3D11_Shader> pixel_shader;
};