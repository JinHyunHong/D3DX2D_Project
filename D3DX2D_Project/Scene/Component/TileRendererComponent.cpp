#include "stdafx.h"
#include "TileRendererComponent.h"

TileRendererComponent::TileRendererComponent(Tool* const tool, Actor* const actor, TransformComponent* const transform) :
	IRendererComponent(tool, actor, transform)
{
}

bool TileRendererComponent::Initialize()
{
	IRendererComponent::Initialize();

	return true;
}

void TileRendererComponent::Update()
{
	if(tile)
		tile->Update();
}

void TileRendererComponent::Destroy()
{
	if (tile)
		tile->Destroy();
}

void TileRendererComponent::AddTile(const std::string& path, const uint& tile_index)
{
	if (tile)
		return;

	tile = std::make_shared<Tile>(tool);
	tile->SetIndex(tile_index);
	auto resource_manager = tool->GetManager<ResourceManager>();
	if (!resource_manager->Load<Tile>(path, tile))
		return;

	if (!tile)
		assert(false);
}
