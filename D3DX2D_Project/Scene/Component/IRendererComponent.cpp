#include "stdafx.h"
#include "IRendererComponent.h"

IRendererComponent::IRendererComponent(Tool* const tool, Actor* const actor, TransformComponent* const transform) :
	IComponent(tool, actor, transform)
{
	base = tool->GetManager<SubsystemManager>()->GetSubsystem<D3D11_Base>();
}

bool IRendererComponent::Initialize()
{
	SetStandardMesh();
	SetStandardMaterial();

	return true;
}

void IRendererComponent::SetStandardMesh()
{
	D3D11_Geometry<D3D11_VertexTexture> geometry;
	Geometry_Generator::CreateQuad(geometry);

	vertex_buffer = std::make_shared<D3D11_VertexBuffer>(base);
	vertex_buffer->Create(geometry.GetVertices());

	index_buffer = std::make_shared<D3D11_IndexBuffer>(base);
	index_buffer->Create(geometry.GetIndices());
}

void IRendererComponent::SetStandardMaterial()
{
	vertex_shader = std::make_shared<D3D11_Shader>(base);
	vertex_shader->Create(Shader_Type::VertexShader, "Assets/Shader/Animation.hlsl");

	pixel_shader = std::make_shared<D3D11_Shader>(base);
	pixel_shader->Create(Shader_Type::PixelShader, "Assets/Shader/Animation.hlsl");

	input_layout = std::make_shared<D3D11_InputLayout>(base);
	input_layout->Create(D3D11_VertexTexture::descs, D3D11_VertexTexture::count, vertex_shader->GetShaderBlob());
}