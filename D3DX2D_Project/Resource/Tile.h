#pragma once
#include "IResource.h"

class Tile :
	public IResource
{
public:
	Tile(class Tool* const tool, const ResourceType type = ResourceType::Unknown);
	~Tile();

	void Update();
	void Destroy();

	bool SaveToFile(const std::string& path) override { return false; }
	bool LoadFromFile(const std::string& path) override;

	auto GetTileTexture() const -> const std::shared_ptr<class D3D11_Texture>& { return tile_texture; }
	void SetTileTexture(const std::shared_ptr<class D3D11_Texture>& tile_texture) { this->tile_texture = tile_texture; }
	void SetTileTexture(const std::string& path);

	auto GetTextureSize() const -> const D3DXVECTOR2& { return texture_size; }
	auto GetOffset() const -> const D3DXVECTOR2& { return offset; }
	auto GetSize() const -> const D3DXVECTOR2& { return size; }
	
	auto GetTexturePath() const { return texture_path; }
	void SetTexturePath(const std::string& texture_path) { this->texture_path = texture_path; }

	auto IsMove() const { return is_move; }
	void SetMove(const bool& is_move) { this->is_move = is_move; }

	auto IsPotal() const { return !potal_tile_name.empty(); }
	void SetPotal(const std::string& potal_tile_name);

	auto GetIndex() const { index; }
	void SetIndex(const int& index) { this->index = index; }

private:
	std::shared_ptr<class D3D11_Texture> tile_texture;
	D3DXVECTOR2 texture_size = D3DXVECTOR2(0.0f, 0.0f);
	std::string texture_path = "";
	D3DXVECTOR2 offset = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 size = D3DXVECTOR2(0.0f, 0.0f);
	std::string potal_tile_name = "";	
	bool is_move = true;
	int index = -1;
};