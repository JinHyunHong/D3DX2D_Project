#pragma once
#include "IRendererComponent.h"

class TileRendererComponent :
	public IRendererComponent
{
public:
	TileRendererComponent(class Tool* const tool, class Actor* const actor,
		class TransformComponent* const transform);
	~TileRendererComponent() = default;

	bool Initialize() override;
	void Update() override;
	void Destroy() override;

	auto GetTile() -> const std::shared_ptr<class Tile> { return tile; }

	auto CreateTile(const std::string& path = "", Xml::XMLElement* root_element = nullptr) -> const std::shared_ptr<Tile>;
	
private:
	auto LoadTile(const std::string& path) -> const std::shared_ptr<Tile>;
	auto LoadTile_Continue(const std::string& path, Xml::XMLElement* root_element = nullptr) -> const std::shared_ptr<Tile>;

private:
	std::shared_ptr<class Tile> tile;
};