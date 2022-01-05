#pragma once
#include "Renderer_Types.h"
#include "Renderer_ConstantBuffers.h"

class Renderer final :
	public ISubsystem
{
public:
	Renderer(class Tool* const tool);
	~Renderer() = default;

	bool Initialize() override;
	void Update() override;
	void Destroy() override {};

	void UpdateRenderables(class Layer* const layer);
	void ClearRenderables();

private:
	void CreateConstantBuffers();
	void CreateRasterizerStates();
	void CreateBlendStates();

	void UpdateCameraBuffer();
	void UpdateObjectBuffer();
	void UpdateTextureBuffer();
	void UpdateColorBuffer();

private:
	void PassMain();
	void RenderMain(class Actor* const actor, class IRendererComponent* component, 
		const RenderableType& type);
	void RenderText(class Actor* const actor);


private:
	class D3D11_Base* base = nullptr;
	class CameraComponent* camera = nullptr;
	std::shared_ptr<class D3D11_Pipeline> pipeline;

	CAMERA_DATA cpu_camera_buffer;
	std::shared_ptr<class D3D11_ConstantBuffer> gpu_camera_buffer;

	TRANSFORM_DATA cpu_object_buffer;
	std::shared_ptr<class D3D11_ConstantBuffer> gpu_object_buffer;

	TEXTURE_DATA cpu_texture_buffer;
	std::shared_ptr<class D3D11_ConstantBuffer> gpu_texture_buffer;

	COLOR_DATA cpu_color_buffer;
	std::shared_ptr<class D3D11_ConstantBuffer> gpu_color_buffer;

private:
	std::map<RenderableType, std::vector<class Actor*>> renderables;
	std::map<RasterizerStateType, std::shared_ptr<class D3D11_RasterizerState>> rasterizers;
	std::map<BlendStateType, std::shared_ptr<class D3D11_BlendState>> blend_states;

private:
	std::unique_ptr<DirectX::SpriteBatch> sprite_batch;
	std::unique_ptr<DirectX::SpriteFont> sprite_font;
};