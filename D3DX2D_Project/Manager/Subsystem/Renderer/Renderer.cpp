#include "stdafx.h"
#include "Renderer.h"
#include "Scene/Actor.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Layer/Layer.h"

Renderer::Renderer(Tool* const tool) :
	ISubsystem(tool)
{
}

bool Renderer::Initialize()
{
	base = tool->GetManager<SubsystemManager>()->GetSubsystem<D3D11_Base>();
	base->CreateBackBuffer(Core::GetInst().GetWidth(), Core::GetInst().GetHeight());
	pipeline = std::make_shared<D3D11_Pipeline>(base);

	CreateConstantBuffers();
	CreateRasterizerStates();
	CreateBlendStates();

	return true;
}

void Renderer::Update()
{
	if (!camera)
		return;

	D3DXMatrixTranspose(&cpu_camera_buffer.view, &camera->GetViewMatrix());
	D3DXMatrixTranspose(&cpu_camera_buffer.proj, &camera->GetProjectionMatrix());
	UpdateCameraBuffer();

	base->Begin();
	PassMain();
	base->End();
}

void Renderer::UpdateRenderables(Layer* const layer)
{
	auto actors = layer->GetActors();

	if (actors.empty())
		return;

	for (const auto& actor : actors)
	{
		auto camera_component = actor->GetComponent<CameraComponent>();
		auto mesh_renderer_component = actor->GetComponent<MeshRendererComponent>();

		if (camera_component)
		{
			renderables[RenderableType::Camera].emplace_back(actor.get());
			camera = camera_component.get();
		}

		if (mesh_renderer_component)
		{
			renderables[RenderableType::Opaque].emplace_back(actor.get());
		}
	}
}

void Renderer::ClearRenderables()
{
	renderables.clear();
}

void Renderer::CreateConstantBuffers()
{
	gpu_camera_buffer = std::make_shared<D3D11_ConstantBuffer>(base);
	gpu_camera_buffer->Create<CAMERA_DATA>();

	gpu_object_buffer = std::make_shared<D3D11_ConstantBuffer>(base);
	gpu_object_buffer->Create<TRANSFORM_DATA>();

	gpu_animation_buffer = std::make_shared<D3D11_ConstantBuffer>(base);
	gpu_animation_buffer->Create<ANIMATION_DATA>();
}

void Renderer::CreateRasterizerStates()
{
	rasterizers[RasterizerStateType::Cull_Front_Solid] = std::make_shared<D3D11_RasterizerState>(base);
	rasterizers[RasterizerStateType::Cull_Front_Solid]->Create(D3D11_CULL_FRONT, D3D11_FILL_SOLID);

	rasterizers[RasterizerStateType::Cull_Back_Solid] = std::make_shared<D3D11_RasterizerState>(base);
	rasterizers[RasterizerStateType::Cull_Back_Solid]->Create(D3D11_CULL_BACK, D3D11_FILL_SOLID);

	rasterizers[RasterizerStateType::Cull_None_Solid] = std::make_shared<D3D11_RasterizerState>(base);
	rasterizers[RasterizerStateType::Cull_None_Solid]->Create(D3D11_CULL_NONE, D3D11_FILL_SOLID);

	rasterizers[RasterizerStateType::Cull_Front_Wireframe] = std::make_shared<D3D11_RasterizerState>(base);
	rasterizers[RasterizerStateType::Cull_Front_Wireframe]->Create(D3D11_CULL_FRONT, D3D11_FILL_WIREFRAME);

	rasterizers[RasterizerStateType::Cull_Back_Wireframe] = std::make_shared<D3D11_RasterizerState>(base);
	rasterizers[RasterizerStateType::Cull_Back_Wireframe]->Create(D3D11_CULL_BACK, D3D11_FILL_WIREFRAME);

	rasterizers[RasterizerStateType::Cull_None_Wireframe] = std::make_shared<D3D11_RasterizerState>(base);
	rasterizers[RasterizerStateType::Cull_None_Wireframe]->Create(D3D11_CULL_NONE, D3D11_FILL_WIREFRAME);
}

void Renderer::CreateBlendStates()
{
	blend_states[BlendStateType::Disabled] = std::make_shared<D3D11_BlendState>(base);
	blend_states[BlendStateType::Disabled]->Create(false);

	blend_states[BlendStateType::Alpha] = std::make_shared<D3D11_BlendState>(base);
	blend_states[BlendStateType::Alpha]->Create(true);
}

void Renderer::UpdateCameraBuffer()
{
	auto buffer = gpu_camera_buffer->Map<CAMERA_DATA>();
	*buffer = cpu_camera_buffer;
	gpu_camera_buffer->Unmap();
}

void Renderer::UpdateObjectBuffer()
{
	auto buffer = gpu_object_buffer->Map<TRANSFORM_DATA>();
	*buffer = cpu_object_buffer;
	gpu_object_buffer->Unmap();
}

void Renderer::UpdateAnimationBuffer()
{
	auto buffer = gpu_animation_buffer->Map<ANIMATION_DATA>();
	*buffer = cpu_animation_buffer;
	gpu_animation_buffer->Unmap();
}

void Renderer::PassMain()
{
	auto actors = renderables[RenderableType::Opaque];
	if (actors.empty())
		return;

	for (const auto& actor : actors)
	{
		auto renderable = actor->GetComponent<MeshRendererComponent>();
		if (!renderable)
			continue;

		auto transform = actor->GetComponent<TransformComponent>();
		if (!transform)
			return;

		D3D11_PipelineState pipeline_state;
		pipeline_state.input_layout = renderable->GetInputLayout().get();
		pipeline_state.primitive_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		pipeline_state.vertex_shader = renderable->GetVertexShader().get();
		pipeline_state.pixel_shader = renderable->GetPixelShader().get();
		pipeline_state.rasterizer_state = rasterizers[RasterizerStateType::Cull_Back_Solid].get();
		pipeline_state.blend_state = blend_states[BlendStateType::Alpha].get();

		if (pipeline->Begin(pipeline_state))
		{
			auto vertex_shader_scope = static_cast<uint>(Shader_Type::VertexShader);
			auto pixel_shader_scope = static_cast<uint>(Shader_Type::PixelShader);

			pipeline->SetVertexBuffer(renderable->GetVertexBuffer().get());
			pipeline->SetIndexBuffer(renderable->GetIndexBuffer().get());

			D3DXMatrixTranspose(&cpu_object_buffer.world, &transform->GetWorldMatrix());
			UpdateObjectBuffer();

			if (auto animator = actor->GetComponent<AnimatorComponent>())
			{
				auto current_keyframe = animator->GetCurrentKeyFrame();
				auto current_animation = animator->GetCurrentAnimation();
				cpu_animation_buffer.sprite_offset = current_keyframe->offset;
				cpu_animation_buffer.sprite_size = current_keyframe->size;
				cpu_animation_buffer.color_key = current_animation->GetColorKey();
				cpu_animation_buffer.texture_size = animator->GetCurrentAnimation()->GetSpriteTextureSize();
				cpu_animation_buffer.is_animated = 1.0f;
				UpdateAnimationBuffer();

				pipeline->SetConstantBuffer(2, vertex_shader_scope | pixel_shader_scope, gpu_animation_buffer.get());
				pipeline->SetShaderResource(0, pixel_shader_scope,
					animator->GetCurrentAnimation()->GetSpriteTexture().get());
			}

			else
			{
				cpu_animation_buffer.sprite_offset = D3DXVECTOR2(0, 0);
				cpu_animation_buffer.sprite_size = D3DXVECTOR2(1, 1);
				cpu_animation_buffer.texture_size = D3DXVECTOR2(1, 1);
				cpu_animation_buffer.is_animated = 0.0f;
				UpdateAnimationBuffer();				

				pipeline->SetConstantBuffer(2, vertex_shader_scope | pixel_shader_scope, gpu_animation_buffer.get());
				pipeline->SetShaderResource_clear(0, pixel_shader_scope);
			}

			pipeline->SetConstantBuffer(0, vertex_shader_scope, gpu_camera_buffer.get());
			pipeline->SetConstantBuffer(1, vertex_shader_scope, gpu_object_buffer.get());
			pipeline->Draw_Indexed(renderable->GetIndexBuffer()->GetCount(),
				renderable->GetIndexBuffer()->GetOffset(), renderable->GetVertexBuffer()->GetOffset());

			pipeline->End();
		}
	}
}
