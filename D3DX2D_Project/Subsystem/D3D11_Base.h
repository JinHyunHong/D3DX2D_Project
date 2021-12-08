#pragma once

class D3D11_Base :
	public ISubsystem
{
public:
	D3D11_Base(class Tool* const tool);
	~D3D11_Base();

	bool Initialize() override;
	void Update() override;
	void Destroy() override;

public:
	void CreateBackBuffer();
	void Begin();
	void End();

private:
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* device_context = nullptr;
	IDXGISwapChain* swapchain = nullptr;
	D3D11_VIEWPORT viewport;
};