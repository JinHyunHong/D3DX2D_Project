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
}

void TileRendererComponent::Destroy()
{
}

auto TileRendererComponent::LoadTile(const std::string& path) -> const std::shared_ptr<Tile>
{
	if (tile)
		return tile;

	if (!path.empty())
	{
		auto resource_manager = tool->GetManager<ResourceManager>();
		tile = resource_manager->Load<Tile>(path);
		return tile;
	}

	return nullptr;
}

auto TileRendererComponent::LoadTile_Continue(const std::string& path, Xml::XMLElement* root_element) -> const std::shared_ptr<Tile>
{
	if (tile)
		return tile;

	// Element가 없다면 처음타일을 생성하는 것이다.
	if (!root_element)
		LoadTile(path);

	if (!path.empty())
	{
		auto resource_manager = tool->GetManager<ResourceManager>();
		tile = resource_manager->Load_Continue<Tile>(path, root_element);
		return tile;
	}

	return nullptr;
}

auto TileRendererComponent::CreateTile(const std::string& path, Xml::XMLElement* root_element) -> const std::shared_ptr<Tile>
{
	if (tile)
	{
		assert(false);
		return nullptr;
	}

	if (!path.empty() && root_element)
		return LoadTile_Continue(path, root_element);

	else if (path.empty())
	{
		tile = std::make_shared<Tile>(tool);
		return tile;
	}

	else
		return LoadTile(path);

	return nullptr;
}
