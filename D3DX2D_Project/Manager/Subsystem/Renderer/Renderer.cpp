#include "stdafx.h"
#include "Renderer.h"
#include "Scene/Actor.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/TextRendererComponent.h"
#include "Scene/Component/ColliderComponent.h"
#include "Scene/Component/TileRendererComponent.h"
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

	// D3DX XTK Initialize
	sprite_batch.reset(new DirectX::SpriteBatch(base->GetDeviceContext()));
	sprite_font.reset(new DirectX::SpriteFont(base->GetDevice(), L"zelda2.spritefont"));

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
		auto text_renderer_component = actor->GetComponent<TextRendererComponent>();
		auto tile_renderer_component = actor->GetComponent<TileRendererComponent>();

		if (camera_component)
		{
			renderables[RenderableType::Camera].emplace_back(actor.get());
			camera = camera_component.get();
		}

		if (mesh_renderer_component || text_renderer_component || tile_renderer_component)
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
		auto render_component = actor->GetComponent<MeshRendererComponent>();
		auto tile_component = actor->GetComponent<TileRendererComponent>();
		auto collider_component = actor->GetComponent<ColliderComponent>();

		if (tile_component)
			RenderMain(actor, tile_component.get(), RenderableType::Opaque);

		if (render_component)
			RenderMain(actor, render_component.get(), RenderableType::Opaque);

		RenderText(actor);
		pipeline->SetRasterizer_clear();

#if defined _DEBUG
	// 디버그 모드시에만 충돌체를 렌더링한다.
		if (collider_component)
			RenderMain(actor, collider_component.get(), RenderableType::Collision);
#endif
	}
}

void Renderer::RenderText(class Actor* const actor)
{
	auto render_text = actor->GetComponent<TextRendererComponent>();

	if (!render_text)
		return;

	auto texts = render_text->GetTexts();
	auto transform = actor->GetComponent<TransformComponent>();
	auto position = transform->GetPosition();
	auto scale = transform->GetScale();

	for (const auto& text : texts)
	{
		sprite_batch->Begin();
		sprite_font->DrawString(sprite_batch.get(), text->text.c_str(),
			DirectX::SimpleMath::Vector2(position.x + text->offset.x, position.y + text->offset.y),
			DirectX::SimpleMath::Color(text->color), 0.0f, DirectX::SimpleMath::Vector2(), 
			DirectX::SimpleMath::Vector2(1.0f, 1.0f));

		sprite_batch->End();
	}
}
