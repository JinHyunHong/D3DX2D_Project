#include "stdafx.h"
#include "MapEditorScene.h"
#include "Layer/Layer.h"
#include "Actor.h"
#include "Scene/Component/MeshRendererComponent.h"
#include "Scene/Component/AnimatorComponent.h"
#include "Scene/Component/TransformComponent.h"
#include "Scene/Component/TileRendererComponent.h"
#include "Scene/Component/ColliderComponent.h"

MapEditorScene::MapEditorScene(Tool* const tool) :
	Scene(tool)
{
	//auto map_layer = CreateLayer("Map");
	//auto map = map_layer->CreateActor();
	//map->SetName("Map");
	//map->AddComponent<MeshRendererComponent>();
	//map->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(2.1f, 2.1f, 1.0f));
	//map->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//auto animator = map->AddComponent<AnimatorComponent>();
	//animator->AddAnimation("Assets/Xml/Map/World_Map.xml");
	//animator->SetCurrentAnimation("World_Map");

	tile_layer = CreateLayer("Tile");
}

MapEditorScene::~MapEditorScene()
{
}

void MapEditorScene::Initialize()
{
	Scene::Initialize();

	graphics->SetBackClearColor(0xff555566);

	Core::GetInst().GetWindow()->CreateInDialog(Dialog_type::MapEditorInit, IDD_MAP_EDITOR_INIT);
}

void MapEditorScene::Input()
{
	auto transform = camera->GetComponent<TransformComponent>();
	auto position = transform->GetPosition();
	auto input_manager = tool->GetManager<SubsystemManager>()->GetSubsystem<InputManager>();
	auto delta_time = timer->GetDeltaTimeMs();

	if (input_manager->GetKeyPress("MoveUp"))
	{
		position.y -= speed * delta_time;
	}

	if (input_manager->GetKeyPress("MoveDown"))
	{
		position.y += speed * delta_time;
	}

	if (input_manager->GetKeyPress("MoveRight"))
	{
		position.x += speed * delta_time;
	}

	if (input_manager->GetKeyPress("MoveLeft"))
	{
		position.x -= speed * delta_time;
	}

	if (input_manager->GetKeyDown("Num1") && speed > 0.1f)
	{
		speed -= 0.05f;
	}

	if (input_manager->GetKeyDown("Num2") && speed < 1.0f)
	{
		speed += 0.05f;
	}

	transform->SetPosition(position);
}

void MapEditorScene::Update()
{
	Input();
	Scene::Update();
	tile_layer->SetActive(false);
}

void MapEditorScene::Destroy()
{
	Scene::Destroy();
}

void MapEditorScene::CreateTiles(const float& width, const float& height)
{
	this->width = width;
	this->height = height;

	for (int i = 0; i < height / 50; ++i)
	{
		for (int j = 0; j < width / 50; ++j)
		{
			auto new_tile = tile_layer->CreateActor();
			new_tile->SetName("tile" + std::to_string(static_cast<uint>(i * height / 50.0f + j)));
			new_tile->GetComponent<TransformComponent>()->SetScale(D3DXVECTOR3(7.0f, 7.0f, 1.0f));
			new_tile->GetComponent<TransformComponent>()->SetPosition(D3DXVECTOR3((j + 1) * 50.0f, (i + 1) * 50.0f, 0.0f));
			new_tile->AddComponent<TileRendererComponent>()->AddTile("Assets/Xml/Map/Empty_Tile.xml", static_cast<uint>(i * height / 50.0f + j));
			new_tile->AddComponent<ColliderComponent>();
		}
	}
}