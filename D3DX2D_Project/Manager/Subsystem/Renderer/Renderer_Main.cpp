#include "stdafx.h"
#include "Renderer.h"
#include "Scene/Actor.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Component/TextRendererComponent.h"
#include "Scene/Component/ColliderComponent.h"
#include "Scene/Component/TileRendererComponent.h"
#include "Scene/Layer/Layer.h"

void Renderer::RenderMain(class Actor* const actor, class IRendererComponent* component, const RenderableType& type)
{
	auto transform = actor->GetComponent<TransformComponent>();
	auto origin_scale = transform->GetScale();
	auto origin_position = transform->GetPosition();

	if (!transform)
		return;
	
	D3D11_PipelineState pipeline_state;
	pipeline_state.input_layout = component->GetInputLayout().get();
	pipeline_state.primitive_topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	pipeline_state.vertex_shader = component->GetVertexShader().get();
	pipeline_state.pixel_shader = component->GetPixelShader().get();

	switch (type)
	{
	case RenderableType::Opaque:
	{
		pipeline_state.rasterizer_state = rasterizers[RasterizerStateType::Cull_None_Solid].get();
		break;
	}
	case RenderableType::Collision:
	{
		pipeline_state.rasterizer_state = rasterizers[RasterizerStateType::Cull_None_Wireframe].get();
		auto offset_scale = origin_scale + actor->GetComponent<ColliderComponent>()->GetOffsetScale();
		auto offset_position = origin_position + actor->GetComponent<ColliderComponent>()->GetOffsetPosition();
		transform->SetScale(offset_scale);
		transform->SetPosition(offset_position);
		break;
	}
	}

	pipeline_state.blend_state = blend_states[BlendStateType::Alpha].get();

	if (pipeline->Begin(pipeline_state))
	{
		auto vertex_shader_scope = static_cast<uint>(Shader_Type::VertexShader);
		auto pixel_shader_scope = static_cast<uint>(Shader_Type::PixelShader);

		pipeline->SetVertexBuffer(component->GetVertexBuffer().get());
		pipeline->SetIndexBuffer(component->GetIndexBuffer().get());

		D3DXMatrixTranspose(&cpu_object_buffer.world, &transform->GetWorldMatrix());
		UpdateObjectBuffer();

		auto animator = actor->GetComponent<AnimatorComponent>();
		auto collider = actor->GetComponent<ColliderComponent>();

		if (animator && type == RenderableType::Opaque)
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

		else if (collider)
		{
			cpu_animation_buffer.sprite_offset = D3DXVECTOR2(0, 0);
			cpu_animation_buffer.sprite_size = D3DXVECTOR2(1, 1);
			cpu_animation_buffer.texture_size = D3DXVECTOR2(1, 1);
			cpu_animation_buffer.is_animated = 0.0f;
			UpdateAnimationBuffer();

			cpu_color_buffer.color = collider->GetColor();
			UpdateColorBuffer();

			pipeline->SetConstantBuffer(2, vertex_shader_scope | pixel_shader_scope, gpu_animation_buffer.get());
			pipeline->SetConstantBuffer(3, vertex_shader_scope | pixel_shader_scope, gpu_color_buffer.get());
			pipeline->SetShaderResource_clear(0, pixel_shader_scope);
		}

		else
		{
			cpu_animation_buffer.sprite_offset = D3DXVECTOR2(0, 0);
			cpu_animation_buffer.sprite_size = D3DXVECTOR2(1, 1);
			cpu_animation_buffer.texture_size = D3DXVECTOR2(1, 1);
			cpu_animation_buffer.is_animated = 0.0f;
			UpdateAnimationBuffer();

			cpu_color_buffer.color = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			UpdateColorBuffer();

			pipeline->SetConstantBuffer(2, vertex_shader_scope | pixel_shader_scope, gpu_animation_buffer.get());
			pipeline->SetConstantBuffer(3, vertex_shader_scope | pixel_shader_scope, gpu_color_buffer.get());
			pipeline->SetShaderResource_clear(0, pixel_shader_scope);
		}

		pipeline->SetConstantBuffer(0, vertex_shader_scope, gpu_camera_buffer.get());
		pipeline->SetConstantBuffer(1, vertex_shader_scope, gpu_object_buffer.get());
		pipeline->Draw_Indexed(component->GetIndexBuffer()->GetCount(),
			component->GetIndexBuffer()->GetOffset(), component->GetVertexBuffer()->GetOffset());

		pipeline->End();
	}

	transform->SetScale(origin_scale);
	transform->SetPosition(origin_position);
}