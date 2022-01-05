#pragma once
#include "IResource.h"

class Texture final
	: public IResource
{
public:
	Texture(class Tool* const tool);
	~Texture();

	bool SaveToFile(const std::string& path) override;
	bool LoadFromFile(const std::string& path) override;
	void SaveToFile_Continue(Xml::XMLDocument& doc) override;
	void SaveToFile_Continue(Xml::XMLDocument& doc, Xml::XMLElement* root_element) override;
	bool LoadFromFile_Continue(Xml::XMLElement* sib_element) override;

	auto GetSpriteTexturePath() const -> const std::string& { return sprite_texture_path; }
	void SetSpriteTexturePath(const std::string& path) { this->sprite_texture_path = path; }

	auto GetSpriteTextureSize() const -> const D3DXVECTOR2& { return sprite_texture_size; }
	void SetSpriteTextureSize(const D3DXVECTOR2& size) { this->sprite_texture_size = size; }

	auto GetSpriteTexture() const -> const std::shared_ptr<class D3D11_Texture>& { return sprite_texture; }
	void SetSpriteTexture(const std::shared_ptr<class D3D11_Texture>& sprite_texture) { this->sprite_texture = sprite_texture; }
	void SetSpriteTexture(const std::string& path);

	auto GetColorKey() const -> const D3DXCOLOR& { return color_key; }
	void SetColorkey(const D3DXCOLOR& color_key) { this->color_key = color_key; }
	void SetColorkey(const uint& color_key) { this->color_key = color_key; }

	auto GetOffset() const -> const D3DXVECTOR2& { return offset; }
	void SetOffset(const D3DXVECTOR2& offset) { this->offset = offset; }

	auto GetSize() const -> const D3DXVECTOR2& { return size; }
	void SetSize(const D3DXVECTOR2& size) { this->size = size; }


private:
	std::shared_ptr<class D3D11_Texture> sprite_texture;
	std::string sprite_texture_path = "";
	D3DXVECTOR2 sprite_texture_size = D3DXVECTOR2(1.0f, 1.0f);
	D3DXCOLOR color_key = D3DXCOLOR(0, 0, 0, 0);
	D3DXVECTOR2 offset{ 0.0f, 0.0f };
	D3DXVECTOR2 size{ 0.0f, 0.0f };
};