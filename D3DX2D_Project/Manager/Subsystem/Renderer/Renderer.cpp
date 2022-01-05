#include "stdafx.h"
#include "Renderer.h"
#include "Scene/Actor.h"
#include "Scene/Component/CameraComponent.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/TextRendererComponent.h"
#include "Scene/Component/ColliderComponent.h"
#include "Scene/Component/TileRendererComponent.h"
#include "Scene/Component/TextureComponent.h"
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
	sprite_font.reset(new DirectX::SpriteFont(base->GetDevice(), L"zelda.spritefont"));

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
		auto collider_component = actor->GetComponent<ColliderComponent>();
		auto texture_component = actor->GetComponent<TextureComponent>();

		if (camera_component)
		{
			renderables[RenderableType::Camera].emplace_back(actor.get());
			camera = camera_component.get();
		}

		if (mesh_renderer_component || text_renderer_component || collider_component || texture_component)
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

	gpu_texture_buffer = std::make_shared<D3D11_ConstantBuffer>(base);
	gpu_texture_buffer->Create<TEXTURE_DATA>();

	gpu_color_buffer = std::make_shared<D3D11_ConstantBuffer>(base);
	gpu_color_buffer->Create<COLOR_DATA>();
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

void Renderer::UpdateTextureBuffer()
{
	auto buffer = gpu_texture_buffer->Map<TEXTURE_DATA>();
	*buffer = cpu_texture_buffer;
	gpu_texture_buffer->Unmap();
}

void Renderer::UpdateColorBuffer()
{
	auto buffer = gpu_color_buffer->Map<COLOR_DATA>();
	*buffer = cpu_color_buffer;
	gpu_color_buffer->Unmap();
}

void Renderer::PassMain()
{
	auto actors = renderables[RenderableType::Opaque];
	if (actors.empty())
		return;

	for (const auto& actor : actors)
	{
		auto render_component = actor->GetComponent<MeshRendererComponent>();
		auto collider_component = actor->GetComponent<ColliderComponent>();

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
	auto position = transform->GetLocalPosition();
	auto scale = transform->GetScale();

	for (auto iter = texts.begin(); iter != texts.end(); ++iter)
	{
		auto text = (*iter).second;
		sprite_batch->Begin();
		sprite_font->DrawString(sprite_batch.get(), text->text.c_str(),
			DirectX::SimpleMath::Vector2(position.x + text->offset_position.x, position.y + text->offset_position.y),
			DirectX::SimpleMath::Color(text->color), 0.0f, DirectX::SimpleMath::Vector2(),
			DirectX::SimpleMath::Vector2(text->scale.x, text->scale.y));

		sprite_batch->End();
	}
}
