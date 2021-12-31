#pragma once
#include "IResource.h"

class Tile :
	public IResource
{
public:
	Tile(class Tool* const tool, const ResourceType type = ResourceType::Unknown);
	~Tile();

	bool SaveToFile(const std::string& path) override { return false; }
	bool LoadFromFile(const std::string& path) override;

	auto IsMove() const { return is_move; }
	void SetMove(const bool& is_move) { this->is_move = is_move; }

	auto IsPotal() const { return !potal_tile_name.empty(); }
	void SetPotal(const std::string& potal_tile_name);

	auto GetIndex() const { index; }
	void SetIndex(const int& index) { this->index = index; }

private:
	std::shared_ptr<class D3D11_Texture> tile_texture;
	std::string potal_tile_name = "";
	bool is_move = true;
	int index = -1;
};