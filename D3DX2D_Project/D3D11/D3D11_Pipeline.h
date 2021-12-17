#pragma once

struct D3D11_PipelineState final : public D3D11
{
	D3D11_InputLayout* input_layout = nullptr;
	D3D11_PRIMITIVE_TOPOLOGY primitive_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	D3D11_Shader* vertex_shader = nullptr;
	D3D11_Shader* pixel_shader = nullptr;
	D3D11_RasterizerState* rasterizer_state = nullptr;
	D3D11_BlendState* blend_state = nullptr;
};

class D3D11_Pipeline final :
	public D3D11
{
public:
	D3D11_Pipeline(class D3D11_Base* const base);
	~D3D11_Pipeline() = default;

	bool Begin(const D3D11_PipelineState& pipeline_state);
	void End();

	void SetVertexBuffer(const class D3D11_VertexBuffer* buffer = nullptr);
	void SetIndexBuffer(const class D3D11_IndexBuffer* buffer = nullptr);
	void SetConstantBuffer(const uint& slot, const uint& scope, const class D3D11_ConstantBuffer* buffer);
	void SetShaderResource(const uint& slot, const uint& scope, const class D3D11_Texture* shader_resource);
	void SetSamplerState(const uint& slot, const uint& scope, const class D3D11_SamplerState* state);

	void SetConstantBuffer_clear(const uint& slot, const uint& scope);
	void SetShaderResource_clear(const uint& slot, const uint& scope);

	void Draw(const uint& vertex_count, const uint& vertex_offset = 0);
	void Draw_Indexed(const uint& index_count, const uint& index_offset = 0, const uint& vertex_offset = 0);


private:
	uint bind_vertex_buffer_id = 0;
	uint bind_index_buffer_id = 0;
	uint bind_input_layout_id = 0;
	uint bind_vertex_shader_id = 0;
	uint bind_pixel_shader_id = 0;
	uint bind_primitive_topology_id = 0;
	uint bind_rasterizer_state_id = 0;
	uint bind_blend_state_id = 0;

};