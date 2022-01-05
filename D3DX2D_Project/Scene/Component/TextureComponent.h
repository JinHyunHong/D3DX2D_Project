#pragma once
#include "IComponent.h"

class TextureComponent :
	public IComponent
{
public:
	TextureComponent(class Tool* const tool, class Actor* const actor,
		class TransformComponent* const transform);
	~TextureComponent() = default;

	bool Initialize() override;
	void Update() override;
	void Destroy() override;

private:
	using texture_pointer = std::shared_ptr<class Texture>;

public:
	auto GetCurrentTexture() const -> const texture_pointer;
	void SetCurrentTexture(const std::string& texture_name);

	auto GetTextures() const -> const std::map<std::string, texture_pointer>& { return textures; }

	void AddTexture(const std::string& texture_name, const texture_pointer& texture);
	void AddTexture(const std::string& path);
	void AddTextures(const std::string& path);
	void AddTexture_Continue(const std::string& path, Xml::XMLElement* sib_element = nullptr);

private:
	std::weak_ptr<class Texture> current_texture;
	std::map<std::string, texture_pointer> textures;
};