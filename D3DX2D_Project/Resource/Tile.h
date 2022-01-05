#pragma once
#include "IResource.h"

class Tile :
	public IResource
{
public:
	Tile(class Tool* const tool, const ResourceType type = ResourceType::Unknown);
	~Tile();

	bool SaveToFile(const std::string& path) override;
	bool LoadFromFile(const std::string& path) override;
	void SaveToFile_Continue(Xml::XMLDocument& doc) override;
	void SaveToFile_Continue(Xml::XMLDocument& doc, Xml::XMLElement* root_element) override;
	bool LoadFromFile_Continue(Xml::XMLElement* sib_element) override;

	auto GetName() const { return name; }
	void SetName(const std::string& name) { this->name = name; }

	auto IsMove() const { return is_move; }
	void SetMove(const bool& is_move) { this->is_move = is_move; }

	auto IsPotal() const { return !potal_tile_name.empty(); }
	void SetPotal(const std::string& potal_tile_name);

private:
	std::shared_ptr<class D3D11_Texture> tile_texture;
	std::string name = "";
	std::string potal_tile_name = "";
	bool is_move = true;
};