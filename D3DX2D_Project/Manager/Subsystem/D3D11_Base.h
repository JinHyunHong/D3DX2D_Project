#pragma once

class D3D11_Base :
	public ISubsystem
{
public:
	D3D11_Base(class Tool* const tool);
	~D3D11_Base();

	bool Initialize() override;
	void Update() override {};
	void Destroy() override {};

public:
	void CreateBackBuffer(const uint& width, const uint& height);
	void Begin();
	void End();

	auto GetDevice() -> ID3D11Device* { return device; }
	auto GetDeviceContext() -> ID3D11DeviceContext* { return device_context; }

private:
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* device_context = nullptr;
	IDXGISwapChain* swap_chain = nullptr;
	D3D11_VIEWPORT viewport = D3D11_VIEWPORT();
	ID3D11RenderTargetView* render_target_view = nullptr;
	D3DXCOLOR clear_color = 0xff555566;
};