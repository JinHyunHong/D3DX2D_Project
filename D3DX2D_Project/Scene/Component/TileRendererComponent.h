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
	void AddTile(const std::string& path, const uint& tile_index);

private:
	std::shared_ptr<class Tile> tile;
};