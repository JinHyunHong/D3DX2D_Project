#pragma once
#include "IResource.h"

/*
	TODO :
*/

class Texture final
	: public IResource
{
public:
	Texture(class Tool* const tool);
	~Texture();

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


private:
	std::shared_ptr<class D3D11_Texture> sprite_texture;
	D3DXVECTOR2 sprite_texture_size = D3DXVECTOR2(1.0f, 1.0f);
	std::string sprite_texture_path = "";
	D3DXCOLOR color_key = D3DXCOLOR(0, 0, 0, 0);
};