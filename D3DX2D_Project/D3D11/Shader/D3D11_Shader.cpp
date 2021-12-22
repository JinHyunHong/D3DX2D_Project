#include "stdafx.h"
#include "D3D11_Shader.h"

D3D11_Shader::D3D11_Shader(D3D11_Base* const base) :
	D3D11(base)
{
}

D3D11_Shader::~D3D11_Shader()
{
	Clear();
}

auto D3D11_Shader::GetEntryPoint() const -> const char*
{
	static const char* empty = nullptr;
	static const char* vs = "VS";
	static const char* ps = "PS";

	switch (type)
	{
	case Shader_Type::VertexShader: return vs;
	case Shader_Type::PixelShader: return ps;
	}

	return nullptr;
}

auto D3D11_Shader::GetTargetProfile() const -> const char*
{
	static const char* empty = nullptr;

#if defined(DIRECTX_VER_11)
	static const char* vs = "vs_5_0";
	static const char* ps = "ps_5_0";

#elif defined(DIRECTX_VER_12)
	static const char* vs = "vs_6_0";
	static const char* ps = "ps_6_0";

#endif

	switch (type)
	{
	case Shader_Type::VertexShader: return vs;
	case Shader_Type::PixelShader: return ps;
	}

	return empty;
}

auto D3D11_Shader::GetShaderModel() const -> const char*
{
#if defined(DIRECTX_VER_11)
	static const char* shader_model = "5_0";

#elif defined(DIRECTX_VER_12)
	static const char* shader_model = "6_0";

#endif
	return shader_model;
}

void D3D11_Shader::Create(const Shader_Type& type, const std::string& shader_path)
{
	this->type = type;
	state = CompilationState::Compiling;
	resource = Compile(type, shader_path);
	state = HasResource() ? CompilationState::Succeeded : CompilationState::Failed;
}

void D3D11_Shader::Clear()
{
	switch (type)
	{
	case Shader_Type::VertexShader:
	{
		auto shader = static_cast<ID3D11VertexShader*>(resource);
		SAFE_RELEASE(shader);
		break;
	}
	case Shader_Type::PixelShader:
	{
		auto shader = static_cast<ID3D11PixelShader*>(resource);
		SAFE_RELEASE(shader);
		break;
	}
	}

	SAFE_RELEASE(blob);
	name = "";
	path = "";
	type = Shader_Type::Unknown;
	state = CompilationState::Unknown;
}

auto D3D11_Shader::Compile(const Shader_Type& type, const std::string& shader_path) -> void*
{
	ID3DBlob* error = nullptr;

	auto h_result = D3DX11CompileFromFileA(shader_path.c_str(), nullptr, nullptr, GetEntryPoint(), GetTargetProfile(), 0, 0, nullptr,
		&blob, &error, nullptr);

	if (error)
	{
		MessageBoxA(nullptr, static_cast<const char*>(error->GetBufferPointer()),
			"Shader_Compile_ERROR", MB_OK);
	}

	assert(SUCCEEDED(h_result));

	void* shader_resource = nullptr;
	if (blob)
	{
		switch (type)
		{
		case Shader_Type::VertexShader:
		{
			h_result = device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr,
				reinterpret_cast<ID3D11VertexShader**>(&shader_resource));
			assert(SUCCEEDED(h_result));
			break;
		}
		case Shader_Type::PixelShader:
		{
			h_result = device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr,
				reinterpret_cast<ID3D11PixelShader**>(&shader_resource));
			assert(SUCCEEDED(h_result));
			break;
		}
		}
	}

	return shader_resource;
}
