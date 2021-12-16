#pragma once

enum class Shader_Type : uint
{
	Unknown = 0U,
	VertexShader = 1U << 0,
	PixelShader = 1U << 1
};

enum class CompilationState : uint
{
	Unknown,
	Compiling,
	Succeeded,
	Failed
};

class D3D11_Shader final :
	public ID3D11
{
public:
	D3D11_Shader(class D3D11_Base* const base);
	~D3D11_Shader();

	auto GetResource()	const { return resource; }
	bool HasResource() const { return resource != nullptr; }

	auto GetName() const -> const std::string& { return name; }
	void SetName(const std::string& name) { this->name = name; }

	auto GetPath() const -> const std::string& { return path; }
	auto GetShaderType() const -> const Shader_Type& { return type; }
	auto GetCompilationState() const -> const CompilationState& { return state; }

	auto GetShaderBlob() const { return blob; }

	auto IsCompiled() const { return state == CompilationState::Succeeded; }

	auto GetEntryPoint() const -> const char*;
	auto GetTargetProfile() const -> const char*;
	auto GetShaderModel() const -> const char*;

	void Create(const Shader_Type& type, const std::string& shader_path);
	void Clear();

private:
	auto Compile(const Shader_Type& type, const std::string& shader_path) -> void*;

private:
	 void* resource;
	 ID3DBlob* blob = nullptr;
	 std::string path = "";
	 std::string name = "";
	 Shader_Type type = Shader_Type::Unknown;
	 CompilationState state = CompilationState::Unknown;
};