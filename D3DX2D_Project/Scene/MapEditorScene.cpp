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
}

MapEditorScene::~MapEditorScene()
{
}

void MapEditorScene::Initialize()
{
	Scene::Initialize();

	graphics->SetBackClearColor(0xff555566);
}

void MapEditorScene::Input()
{
	auto transform = camera->GetComponent<TransformComponent>();
	auto position = transform->GetPosition();
	auto input_manager = tool->GetManager<SubsystemManager>()->GetSubsystem<InputManager>();

	if (input_manager->GetKeyPress("MoveUp"))
	{
		position.y--;
	}

	if (input_manager->GetKeyPress("MoveDown"))
	{
		position.y++;
	}

	if (input_manager->GetKeyPress("MoveRight"))
	{
		position.x++;
	}

	if (input_manager->GetKeyPress("MoveLeft"))
	{
		position.x--;
	}

	transform->SetPosition(position);
}

void MapEditorScene::Update()
{
	Input();
	Scene::Update();
}

void MapEditorScene::Destroy()
{
	Scene::Destroy();
}
