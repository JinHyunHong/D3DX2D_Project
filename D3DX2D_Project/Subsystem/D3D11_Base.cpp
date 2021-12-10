#include "stdafx.h"
#include "D3D11_Base.h"
#include "Core/Core.h"

D3D11_Base::D3D11_Base(class Tool* const tool) :
	ISubsystem(tool)
{
}

D3D11_Base::~D3D11_Base()
{
	SAFE_RELEASE(render_target_view);
	SAFE_RELEASE(swap_chain);
	SAFE_RELEASE(device_context);
	SAFE_RELEASE(device);
}

bool D3D11_Base::Initialize()
{
	std::vector<D3D_FEATURE_LEVEL> feature_levels{ D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };

	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(DXGI_SWAP_CHAIN_DESC));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = 0;
	desc.BufferDesc.Height = 0;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = Core::GetInst().GetWindow()->GetWindowHandle();
	desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	desc.Windowed = TRUE;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;

	auto h_result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
		feature_levels.data(), feature_levels.size(), D3D11_SDK_VERSION, &desc, &swap_chain, &device, nullptr, &device_context);

	assert(SUCCEEDED(h_result));
	return true;
}

void D3D11_Base::CreateBackBuffer(const uint& width, const uint& height)
{
	auto h_result = swap_chain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);
	assert(SUCCEEDED(h_result));

	ID3D11Texture2D* back_buffer = nullptr;
	h_result = swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&back_buffer));
	assert(SUCCEEDED(h_result));

	h_result = device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view);
	assert(SUCCEEDED(h_result));

	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(width);
	viewport.Height = static_cast<float>(height);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	
	SAFE_RELEASE(back_buffer);
}

void D3D11_Base::Begin()
{
	device_context->OMSetRenderTargets(1, &render_target_view, nullptr);
	device_context->RSSetViewports(1, &viewport);
	device_context->ClearRenderTargetView(render_target_view, clear_color);
}

void D3D11_Base::End()
{
	auto h_result = swap_chain->Present(1, 0);
	assert(SUCCEEDED(h_result));
}
